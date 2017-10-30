#include "typesloader.h"
#include "util.h"
#include "path.h"
#include <QStringList>
#include <QFile>
#include <QXmlStreamReader>
#include <QRegExp>
#include <qdesigner_utils_p.h>

#define TYPE "type"
#define INFORMATION "information"
#define RESOURCES "resources"
#define RESOURCE "resource"
#define ATTRIBUTES "attributes"
#define ATTRIBUTE "attribute"
#define LANGUAGES "languages"
#define LANGUAGE "language"
#define SENTENCE "sentence"
#define CODE "Code"
#define ID "ID"
#define EN_US "en_us"
#define E2VDOM "e2vdom"
#define EVENTS "events"
#define EVENT "event"
#define PARAMETER "parameter"
#define ACTIONS "actions"
#define ACTION "action"

static QRegExp langRegExp("#Lang\\(([^\\)]+)\\)");
static QRegExp resRegExp("#Res\\(([^\\)]+)\\)");

QMap<QString, QStringList> makeVisibleProperties()
{
    QMap<QString, QStringList> ret;
    ret["text"].push_back("value");
    ret["richtext"].push_back("value");
    return ret;
}

QMap<QString, QStringList> visibleProperties = makeVisibleProperties();

inline bool IsVisibleProperty(const QString &typeName, const QString &attrName)
{
    QMap<QString, QStringList>::const_iterator i = visibleProperties.find(typeName);
    if (i != visibleProperties.end() && i->contains(attrName))
        return true;
    return false;
}

QMap<QString, QMap<QString, QString> > makeTranslationVdomToQml()
{
    QMap<QString, QMap<QString, QString> > ret;
    ret["xmldialog"]["modal"] = "is_modal";
    return ret;
}

QMap<QString, QMap<QString, QString> > makeTranslationQmlToVdom()
{
    QMap<QString, QMap<QString, QString> > ret;
    ret["xmldialog"]["is_modal"] = "modal";
    return ret;
}

static QMap<QString, QMap<QString, QString> > translationVdomToQml = makeTranslationVdomToQml();
static QMap<QString, QMap<QString, QString> > translationQmlToVdom = makeTranslationQmlToVdom();

static QString TranslateAttribute(const QString &typeName, const QString &attrName,
                                  const QMap<QString, QMap<QString, QString> > &m)
{
    QMap<QString, QMap<QString, QString> >::const_iterator t = m.find(typeName);
    if (t != m.end()) {
        QMap<QString, QString>::const_iterator a = t->find(attrName);
        if (a != t->end())
            return a.value();
    }
    return attrName;
}

QString TranslateAttributeVdomToQml(const QString &typeName, const QString &attrName)
{
    return TranslateAttribute(typeName, attrName, translationVdomToQml);
}

QString TranslateAttributeQmlToVdom(const QString &typeName, const QString &attrName)
{
    return TranslateAttribute(typeName, attrName, translationQmlToVdom);
}

bool VdomTypeInfo::isContainer() const
{
    return (container == "2" || container == "3");
}

bool VdomTypeInfo::isTopContainer() const
{
    return (container == "3");
}

QMap<QString, AttributeInfo>::const_iterator VdomTypeInfo::findAttribute(const QString &name, bool translate) const
{
    QString _name = translate ? TranslateAttributeQmlToVdom(typeName, name) : name;
    return attributes.find(_name);
}

bool VdomTypeInfo::hasAttribute(const QString &name, bool translate) const
{
    QString _name = translate ? TranslateAttributeQmlToVdom(typeName, name) : name;
    return attributes.contains(_name);
}

bool AttributeInfo::isDropDown() const
{
    return codeInterface.startsWith("DropDown");
}

bool AttributeInfo::isNumber() const
{
    return codeInterface.startsWith("Number");
}

bool AttributeInfo::isTextField() const
{
    return codeInterface.startsWith("TextField");
}

bool AttributeInfo::isMultiLine() const
{
    return codeInterface.startsWith("MultiLine");
}

bool AttributeInfo::isColor() const
{
    return codeInterface.startsWith("Color");
}

bool AttributeInfo::isFont() const
{
    return codeInterface.startsWith("Font");
}

bool AttributeInfo::isFile() const
{
    return codeInterface.startsWith("File");
}

bool AttributeInfo::isPageLink() const
{
    return codeInterface.startsWith("PageLink");
}

bool AttributeInfo::isObjectList() const
{
    return codeInterface.startsWith("ObjectList");
}

bool AttributeInfo::isExternalEditor() const
{
    return codeInterface.startsWith("ExternalEditor");
}

QVariant AttributeInfo::getDropDownValue(const QVariant &srcValue) const
{
    if (srcValue.type() == QVariant::Int) {
        QVariant v;
        int idx = srcValue.toInt();
        qdesigner_internal::PropertySheetEnumValue e = qvariant_cast<qdesigner_internal::PropertySheetEnumValue>(defaultValue);
        if (idx < e.metaEnum.keyToValueMap().size()) {
            qdesigner_internal::PropertySheetEnumValue pse = qdesigner_internal::PropertySheetEnumValue(idx, e.metaEnum);
            v.setValue(pse);
            return v;
        }
    }
    return srcValue;
}

bool AttributeInfo::equalsToDefault(const QVariant &v) const
{
    if (v.type() == QVariant::Bool && QString::number(v.toInt()) == defaultValueStr)
        return true;
    else if (QString(v.typeName()) == "qdesigner_internal::PropertySheetStringValue" &&
             qvariant_cast<qdesigner_internal::PropertySheetStringValue>(v).value() == defaultValueStr)
        return true;
    else if (isColor() && ParseColor(v.toString()) == ParseColor(defaultValueStr))
        return true;
    else if (isFont() && *v.toString().split(',').begin() == *defaultValueStr.split(',').begin())
        return true;
    else if (isDropDown() && QString(v.typeName()) == "qdesigner_internal::PropertySheetEnumValue" &&
             dropDownKeys[qvariant_cast<qdesigner_internal::PropertySheetEnumValue>(v).value] == defaultValueStr)
        return true;
    else if (v.type() != QVariant::UserType && v.toString() == defaultValueStr)
        return true;
    else if (isFile() && QString(v.typeName()) == "qdesigner_internal::PropertySheetPixmapValue" &&
             qvariant_cast<qdesigner_internal::PropertySheetPixmapValue>(v).path() == DefaultPath("/"))
        return true;
    else
        return false;
}

QVariant MakeDefaultValue(const VdomTypeInfo &/*type*/, const AttributeInfo &attr)
{
    if (attr.attrName == "visible")
        return QVariant((attr.defaultValueStr == "1"));
    else if (attr.isNumber())
        return QVariant(attr.defaultValueStr.toInt());
    else if (attr.isColor()) {
        QVariant ret(QVariant::Color);
        ret.setValue(ParseColor(attr.defaultValueStr));
        return ret;
    } else if (attr.isFont()) {
        QFont f;
        f.fromString(*attr.defaultValueStr.split(',').begin());
        return QVariant(f);
    } else if (attr.isDropDown()) {
        QVariant ret;
        qdesigner_internal::DesignerMetaEnum e(attr.attrName, "", "");
        for (QMap<int, QString>::const_iterator i=attr.dropDownValues.begin(); i!=attr.dropDownValues.end(); i++)
            e.addKey(i.key(), i.value());
        int idx = 0;
        QMap<int, QString>::const_iterator i = FindFirst(attr.dropDownKeys, attr.defaultValueStr);
        if (i != attr.dropDownKeys.end())
            idx = i.key();
        ret.setValue(qdesigner_internal::PropertySheetEnumValue(idx, e));
        return ret;
    } else if (attr.isFile()) {
        QVariant ret;
        ret.setValue(qdesigner_internal::PropertySheetPixmapValue(DefaultPath("/")));
        return ret;
    } else {
        QVariant ret;
        ret.setValue(qdesigner_internal::PropertySheetStringValue(attr.defaultValueStr, false));
        return ret;
    }
}

QString GetResId(const QString &data)
{
    if (resRegExp.indexIn(data, 0) != -1)
        return resRegExp.cap(1);
    return QString();
}

QString ResolveLang(const VdomTypeInfo &typeInfo, const QString &data, const QString &langId)
{
    if (!typeInfo.lang.contains(langId))
        return data;
    QString result = data;
    int start = 0;
    while ((start = langRegExp.indexIn(result, start)) != -1) {
        int length = langRegExp.matchedLength();
        QString sentenceId = langRegExp.cap(1);
        if (!sentenceId.isEmpty() && typeInfo.lang[langId].contains(sentenceId)) {
            QString sentence = typeInfo.lang[langId][sentenceId];
            result.replace(start, length, sentence);
            start += sentence.length();
        } else
            start += length;
    }
    return result;
}

QMap<QString, QString> LoadLanguage(QXmlStreamReader &xml)
{
    QMap<QString, QString> ret;
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, LANGUAGE))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, SENTENCE)) {
                QString sentId = attr(xml, ID);
                if (!sentId.isEmpty())
                    ret[sentId] = get(xml);
            }
        }
        xml.readNext();
    }
    return ret;
}

QMap<QString, QMap<QString, QString> > LoadLanguages(QXmlStreamReader &xml)
{
    QMap<QString, QMap<QString, QString> > ret;
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, LANGUAGES))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, LANGUAGE)) {
                QString langId = attr(xml, CODE);
                if (!langId.isEmpty())
                    ret[langId.toLower()] = LoadLanguage(xml);
            }
        }
        xml.readNext();
    }
    return ret;
}

void ParseDropDown(AttributeInfo &attr)
{
    QString v = attr.codeInterface.mid(10, attr.codeInterface.size()-12);
    QStringList ret = v.split(")|(");
    int idx = 0;
    for (QStringList::iterator i=ret.begin(); i!=ret.end(); i++) {
        int sep = i->lastIndexOf('|');
        attr.dropDownKeys[idx] = i->mid(sep+1);
        attr.dropDownValues[idx] = i->left(sep);
        idx++;
    }
}

AttributeInfo LoadAttribute(QXmlStreamReader &xml)
{
    AttributeInfo ret;
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, ATTRIBUTE))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, "name")) ret.attrName = get(xml);
            else if (equals(xml, "displayname")) ret.displayName = get(xml);
            else if (equals(xml, "defaultvalue")) ret.defaultValueStr = get(xml);
            else if (equals(xml, "visible")) ret.visible = (get(xml).toInt() == 1);
            else if (equals(xml, "interfacetype")) ret.interfaceType = get(xml);
            else if (equals(xml, "codeinterface")) ret.codeInterface = get(xml);
            else if (equals(xml, "colorgroup")) ret.colorGroup = get(xml);
        }
        xml.readNext();
    }
    if (ret.isDropDown())
        ParseDropDown(ret);
    return ret;
}

void LoadAttributes(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, ATTRIBUTES))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, ATTRIBUTE)) {
                AttributeInfo attr = LoadAttribute(xml);
                ret.attributes[attr.attrName] = attr;
            }
        }
        xml.readNext();
    }
}

void LoadEvent(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    QString name = attr(xml, "Name");
    QStringList param;
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, EVENT))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, PARAMETER)) {
                QString p = attr(xml, "Name");
                if (!p.isEmpty())
                    param.append(p);
            }
        }
        xml.readNext();
    }
    if (!name.isEmpty())
        ret.e2vdomEvents[name] = param;
}

void LoadEvents(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, EVENTS))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, EVENT))
                LoadEvent(xml, ret);
        }
        xml.readNext();
    }
}

void LoadAction(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    QString name = attr(xml, "MethodName");
    QStringList param;
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, ACTION))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, PARAMETER)) {
                QString p = attr(xml, "ScriptName");
                if (!p.isEmpty())
                    param.append(p);
            }
        }
        xml.readNext();
    }
    if (!name.isEmpty())
        ret.e2vdomActions[name] = param;
}

void LoadActions(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, ACTIONS))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, ACTION))
                LoadAction(xml, ret);
        }
        xml.readNext();
    }
}

void LoadE2vdom(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, E2VDOM))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, EVENTS))
                LoadEvents(xml, ret);
            else if (equals(xml, ACTIONS))
                LoadActions(xml, ret);
        }
        xml.readNext();
    }
}

void LoadResource(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    if (attr(xml, ID) == ret.iconId) {
        QPixmap p;
        p.loadFromData(QByteArray::fromBase64(get(xml).toLatin1()));
        ret.icon = QIcon(p);
    }
}

void LoadResources(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, RESOURCES))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, RESOURCE))
                LoadResource(xml, ret);
        }
        xml.readNext();
    }
}

void LoadInformation(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, INFORMATION))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, "name")) ret.typeName = get(xml);
            else if (equals(xml, "displayname")) ret.displayName = get(xml);
            else if (equals(xml, "category")) ret.category = get(xml);
            else if (equals(xml, "container")) ret.container = get(xml);
            else if (equals(xml, "rendertype")) ret.renderType = get(xml);
            else if (equals(xml, "containers")) {
                ret.containers = get(xml).split(",", QString::SkipEmptyParts);
                for (QStringList::iterator i=ret.containers.begin(); i!=ret.containers.end(); i++)
                    *i = i->trimmed();
            } else if (equals(xml, "icon")) ret.iconId = GetResId(get(xml));
        }
        xml.readNext();
    }
}

VdomTypeInfo LoadType(QXmlStreamReader &xml)
{
    VdomTypeInfo ret;
    xml.readNext();
    while (!xml.atEnd() && !(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, TYPE))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, INFORMATION))
                LoadInformation(xml, ret);
            else if (equals(xml, ATTRIBUTES))
                LoadAttributes(xml, ret);
            else if (equals(xml, LANGUAGES))
                ret.lang = LoadLanguages(xml);
            else if (equals(xml, RESOURCES))
                LoadResources(xml, ret);
            else if (equals(xml, E2VDOM))
                LoadE2vdom(xml, ret);
        }
        xml.readNext();
    }
    return ret;
}

QMap<QString, VdomTypeInfo> LoadTypes(const QString &filename)
{
    QMap<QString, VdomTypeInfo> ret;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical("Can't open types file \'%s\': %s", filename.toLatin1().constData(), file.errorString().toLatin1().constData());
        return ret;
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (equals(xml, TYPE)) {
                VdomTypeInfo t = LoadType(xml);
                t.displayName = ResolveLang(t, t.displayName, EN_US);
                t.category = ResolveLang(t, t.category, EN_US);
                for (QMap<QString, AttributeInfo>::iterator i=t.attributes.begin(); i!=t.attributes.end(); i++) {
                    i->displayName = ResolveLang(t, i->displayName, EN_US);
                    if (i->isDropDown())
                        for (QMap<int, QString>::iterator j=i->dropDownValues.begin(); j!=i->dropDownValues.end(); j++)
                            *j = ResolveLang(t, *j, EN_US);
                    i->defaultValue = MakeDefaultValue(t, *i);
                    if (IsVisibleProperty(t.typeName, i->attrName))
                        i->visible = true;
                }
                ret[t.typeName] = t;
            }
        }
    }

    return ret;
}

