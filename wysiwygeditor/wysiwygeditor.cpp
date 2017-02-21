#include "wysiwygeditor.h"
#include "widgetsfile.h"
#include "path.h"

static const QString defaultContent = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<ui version=\"4.0\">"
" <class>Container</class>"
" <widget class=\"Container\" name=\"container\">"
"  <property name=\"geometry\">"
"   <rect>"
"    <x>0</x>"
"    <y>0</y>"
"    <width>400</width>"
"    <height>300</height>"
"   </rect>"
"  </property>"
" </widget>"
" <resources/>"
" <connections/>"
"</ui>";

WysiwygEditor::WysiwygEditor() : designer(NULL)
{
}

WysiwygEditor::~WysiwygEditor()
{
    delete designer;
    designer = NULL;
}

void WysiwygEditor::initialize(QWidget *parent, const QString &widgetsFileName, const QString &pluginPath)
{
    Q_ASSERT(!designer);
    Q_ASSERT(parent);

    QString widgetsFile = widgetsFileName.isEmpty() ? defaultPath(defaultWidgetsFileName) : widgetsFileName;
    WriteWidgetsFile(widgetsFile, CreateWidgetsXml());

    designer = new Designer();
    designer->initialize(parent, this, widgetsFile,
                         pluginPath.isEmpty() ? defaultPath(defaultPluginPath) : pluginPath);
}

QWidget* WysiwygEditor::widgetBox() const
{
    Q_ASSERT(designer);
    return designer->widgetBox();
}

QWidget* WysiwygEditor::form() const
{
    Q_ASSERT(designer);
    return designer->form();
}

QWidget* WysiwygEditor::objectInspector() const
{
    Q_ASSERT(designer);
    return designer->objectInspector();
}

QWidget* WysiwygEditor::propertyEditor() const
{
    Q_ASSERT(designer);
    return designer->propertyEditor();
}

void WysiwygEditor::setContent(const QString &content)
{
    Q_ASSERT(designer);
    if (!content.isEmpty()) {
        designer->setContent(content);
    } else {
        designer->setContent(defaultContent);
    }
}

QString WysiwygEditor::getContent() const
{
    Q_ASSERT(designer);
    return designer->getContent();
}

void WysiwygEditor::widgetManaged(QWidget*)
{
    // TODO:
}
