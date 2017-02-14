#include "wysiwygeditor.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

static const QString defaultContent = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<ui version=\"4.0\">"
" <class>Container</class>"
" <widget class=\"QWidget\" name=\"Container\">"
"  <property name=\"geometry\">"
"   <rect>"
"    <x>0</x>"
"    <y>0</y>"
"    <width>400</width>"
"    <height>300</height>"
"   </rect>"
"  </property>"
"  <property name=\"windowTitle\">"
"   <string></string>"
"  </property>"
" </widget>"
" <resources/>"
" <connections/>"
"</ui>";

// default paths relative to the application module directory
static const QString defaultWidgetsFileName = "/widgets.xml";
static const QString defaultPluginPath = "/designer";

QString defaultPath(const QString &p)
{
    static QString appPath = QFileInfo(QCoreApplication::applicationFilePath()).absoluteDir().path();
    return appPath + p;
}

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
    designer = new Designer();
    designer->initialize(parent, this,
                         widgetsFileName.isEmpty() ? defaultPath(defaultWidgetsFileName) : widgetsFileName,
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
