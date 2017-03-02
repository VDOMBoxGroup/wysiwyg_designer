#include "typesloader.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QRegExp>

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

inline QString get(QXmlStreamReader &xml)
{
    return xml.readElementText().trimmed();
}

inline QString extractLang(const QString &s)
{
    if (langRegExp.indexIn(s) > -1)
        return langRegExp.cap(1);
    else
        return QString();
}

inline bool equals(const QXmlStreamReader &xml, const QString &str)
{
    return (xml.name().compare(str, Qt::CaseInsensitive) == 0);
}

inline QString langdata(const VdomTypeInfo &typeInfo, const QString &data, const QString &langId)
{
    if (!typeInfo.lang.contains(langId))
        return data;
    QString sentenceId = extractLang(data);
    if (sentenceId.isEmpty())
        return data;
    if (!typeInfo.lang[langId].contains(sentenceId))
        return data;
    return typeInfo.lang[langId][sentenceId];
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

AttributeInfo LoadAttribute(QXmlStreamReader &xml)
{
    AttributeInfo ret;
    xml.readNext();
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && equals(xml, ATTRIBUTE))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (equals(xml, "name")) ret.attrName = get(xml);
            else if (equals(xml, "displayname")) ret.displayName = get(xml);
            else if (equals(xml, "defaultvalue")) ret.defaultValue = get(xml);
            else if (equals(xml, "visible")) ret.visible = (get(xml).toInt() == 1);
            else if (equals(xml, "interfacetype")) ret.interfaceType = get(xml);
            else if (equals(xml, "codeinterface")) ret.codeInterface = get(xml);
            else if (equals(xml, "colorgroup")) ret.colorGroup = get(xml);
        }
        xml.readNext();
    }
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
                t.displayName = langdata(t, t.displayName, EN_US);
                t.category = langdata(t, t.category, EN_US);
                for (QMap<QString, AttributeInfo>::iterator i=t.attributes.begin(); i!=t.attributes.end(); i++)
                    i->displayName = langdata(t, i->displayName, EN_US);
                ret[t.typeName] = t;
            }
        }
    }

    return ret;
}
