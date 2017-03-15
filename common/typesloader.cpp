#include "typesloader.h"
#include "util.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QRegExp>
#include <qdesigner_utils_p.h>

#define TYPE "type"
#define INFORMATION "information"
#define ATTRIBUTES "attributes"
#define ATTRIBUTE "attribute"
#define LANGUAGES "languages"
#define LANGUAGE "language"
#define SENTENCE "sentence"
#define CODE "Code"
#define ID "ID"
#define EN_US "en_us"

QRegExp langRegExp("#Lang\\(([^\\)]+)\\)");

bool VdomTypeInfo::isContainer() const
{
    return (container == "2" || container == "3");
}

bool VdomTypeInfo::isTopContainer() const
{
    return (container == "3");
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
    else if (isColor() && parseColor(v.toString()) == parseColor(defaultValueStr))
        return true;
    else if (isFont() && *v.toString().split(',').begin() == *defaultValueStr.split(',').begin())
        return true;
    else if (isDropDown() && QString(v.typeName()) == "qdesigner_internal::PropertySheetEnumValue" &&
             dropDownKeys[qvariant_cast<qdesigner_internal::PropertySheetEnumValue>(v).value] == defaultValueStr)
        return true;
    else if (v.type() != QVariant::UserType && v.toString() == defaultValueStr)
        return true;
    else
        return false;
}

QVariant makeDefaultValue(const VdomTypeInfo &/*type*/, const AttributeInfo &attr)
{
    if (attr.attrName == "visible")
        return QVariant((attr.defaultValueStr == "1"));
    else if (attr.isNumber())
        return QVariant(attr.defaultValueStr.toInt());
    else if (attr.isColor()) {
        QVariant ret(QVariant::Color);
        ret.setValue(parseColor(attr.defaultValueStr));
        return ret;
    }
    else if (attr.isFont()) {
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
        qdesigner_internal::PropertySheetEnumValue pse = qdesigner_internal::PropertySheetEnumValue(idx, e);
        ret.setValue(pse);
        return ret;
    }
    return QVariant(attr.defaultValueStr);
}

inline QString get(QXmlStreamReader &xml)
{
    return xml.readElementText().trimmed();
}

inline bool equals(const QXmlStreamReader &xml, const QString &str)
{
    return (xml.name().compare(str, Qt::CaseInsensitive) == 0);
}

QString resolveLang(const VdomTypeInfo &typeInfo, const QString &data, const QString &langId)
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
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, LANGUAGE))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, SENTENCE)) {
                QXmlStreamAttributes attr = xml.attributes();
                if (attr.hasAttribute(ID) && !attr.value(ID).isEmpty())
                    ret[attr.value(ID).toString()] = get(xml);
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
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, LANGUAGES))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, LANGUAGE)) {
                QXmlStreamAttributes attr = xml.attributes();
                if (attr.hasAttribute(CODE) && !attr.value(CODE).isEmpty())
                    ret[attr.value(CODE).toString().toLower()] = LoadLanguage(xml);
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
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, ATTRIBUTE))) {
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
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, ATTRIBUTES))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, ATTRIBUTE)) {
                AttributeInfo attr = LoadAttribute(xml);
                ret.attributes[attr.attrName] = attr;
            }
        }
        xml.readNext();
    }
}

void LoadInformation(QXmlStreamReader &xml, VdomTypeInfo &ret)
{
    xml.readNext();
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, INFORMATION))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, "name")) ret.typeName = get(xml);
            else if (equals(xml, "displayname")) ret.displayName = get(xml);
            else if (equals(xml, "category")) ret.category = get(xml);
            else if (equals(xml, "container")) ret.container = get(xml);
            else if (equals(xml, "containers")) ret.containers = get(xml).split(",");
        }
        xml.readNext();
    }
}

VdomTypeInfo LoadType(QXmlStreamReader &xml)
{
    VdomTypeInfo ret;
    xml.readNext();
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, TYPE))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, INFORMATION))
                LoadInformation(xml, ret);
            else if (equals(xml, ATTRIBUTES))
                LoadAttributes(xml, ret);
            else if (equals(xml, LANGUAGES))
                ret.lang = LoadLanguages(xml);
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
        qDebug("Can't open types file \'%s\': %s", filename.toLatin1().constData(), file.errorString().toLatin1().constData());
        return ret;
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (equals(xml, TYPE)) {
                VdomTypeInfo t = LoadType(xml);
                t.displayName = resolveLang(t, t.displayName, EN_US);
                t.category = resolveLang(t, t.category, EN_US);
                for (QMap<QString, AttributeInfo>::iterator i=t.attributes.begin(); i!=t.attributes.end(); i++) {
                    i->displayName = resolveLang(t, i->displayName, EN_US);
                    if (i->isDropDown())
                        for (QMap<int, QString>::iterator j=i->dropDownValues.begin(); j!=i->dropDownValues.end(); j++)
                            *j = resolveLang(t, *j, EN_US);
                    i->defaultValue = makeDefaultValue(t, *i);
                }
                ret[t.typeName] = t;
            }
        }
    }

    return ret;
}
