#ifndef VDOMCLASSES_H
#define VDOMCLASSES_H

#include "vdomclassfactory.h"
#include <QMap>
#include <QString>

// classes

class FormImage: public VDOMWidget
{
    Q_OBJECT
public:
    FormImage(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormImage(parent); }
};

class PrintToWebAction: public VDOMWidget
{
    Q_OBJECT
public:
    PrintToWebAction(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new PrintToWebAction(parent); }
};

class FormList: public VDOMWidget
{
    Q_OBJECT
public:
    FormList(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormList(parent); }
};

class SVGBook: public VDOMWidget
{
    Q_OBJECT
public:
    SVGBook(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new SVGBook(parent); }
};

class FullCalendar: public VDOMWidget
{
    Q_OBJECT
public:
    FullCalendar(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FullCalendar(parent); }
};

class Hypertext: public VDOMWidget
{
    Q_OBJECT
public:
    Hypertext(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Hypertext(parent); }
};

class FullTextIndex: public VDOMWidget
{
    Q_OBJECT
public:
    FullTextIndex(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FullTextIndex(parent); }
};

class ProgressBar: public VDOMWidget
{
    Q_OBJECT
public:
    ProgressBar(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new ProgressBar(parent); }
};

class DesktopApplication: public VDOMWidget
{
    Q_OBJECT
public:
    DesktopApplication(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DesktopApplication(parent); }
};

class Table: public VDOMWidget
{
    Q_OBJECT
public:
    Table(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Table(parent); }
};

class Calendar: public VDOMWidget
{
    Q_OBJECT
public:
    Calendar(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Calendar(parent); }
};

class Accordion: public VDOMWidget
{
    Q_OBJECT
public:
    Accordion(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Accordion(parent); }
};

class FormRadiobutton: public VDOMWidget
{
    Q_OBJECT
public:
    FormRadiobutton(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormRadiobutton(parent); }
};

class DatabaseTable: public VDOMWidget
{
    Q_OBJECT
public:
    DatabaseTable(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DatabaseTable(parent); }
};

class DynamicObjectView: public VDOMWidget
{
    Q_OBJECT
public:
    DynamicObjectView(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DynamicObjectView(parent); }
};

class FormText: public VDOMWidget
{
    Q_OBJECT
public:
    FormText(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormText(parent); }
};

class DesktopApplicationForm: public VDOMWidget
{
    Q_OBJECT
public:
    DesktopApplicationForm(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DesktopApplicationForm(parent); }
};

class Growl: public VDOMWidget
{
    Q_OBJECT
public:
    Growl(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Growl(parent); }
};

class Indexconnector: public VDOMWidget
{
    Q_OBJECT
public:
    Indexconnector(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Indexconnector(parent); }
};

class Container: public VDOMWidget
{
    Q_OBJECT
public:
    Container(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Container(parent); }
};

class FormTextEditor: public VDOMWidget
{
    Q_OBJECT
public:
    FormTextEditor(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormTextEditor(parent); }
};

class XMLContainer: public VDOMWidget
{
    Q_OBJECT
public:
    XMLContainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new XMLContainer(parent); }
};

class Breadcrumbs: public VDOMWidget
{
    Q_OBJECT
public:
    Breadcrumbs(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Breadcrumbs(parent); }
};

class WebDAVContainer: public VDOMWidget
{
    Q_OBJECT
public:
    WebDAVContainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new WebDAVContainer(parent); }
};

class FormCheckbox: public VDOMWidget
{
    Q_OBJECT
public:
    FormCheckbox(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormCheckbox(parent); }
};

class Shortcut: public VDOMWidget
{
    Q_OBJECT
public:
    Shortcut(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Shortcut(parent); }
};

class Connector: public VDOMWidget
{
    Q_OBJECT
public:
    Connector(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Connector(parent); }
};

class TableCell: public VDOMWidget
{
    Q_OBJECT
public:
    TableCell(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new TableCell(parent); }
};

class DesktopApplicationScript: public VDOMWidget
{
    Q_OBJECT
public:
    DesktopApplicationScript(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DesktopApplicationScript(parent); }
};

class EditableResource: public VDOMWidget
{
    Q_OBJECT
public:
    EditableResource(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new EditableResource(parent); }
};

class Carousel: public VDOMWidget
{
    Q_OBJECT
public:
    Carousel(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Carousel(parent); }
};

class Text: public VDOMWidget
{
    Q_OBJECT
public:
    Text(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Text(parent); }
};

class FormButton: public VDOMWidget
{
    Q_OBJECT
public:
    FormButton(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormButton(parent); }
};

class XMLDialog: public VDOMWidget
{
    Q_OBJECT
public:
    XMLDialog(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new XMLDialog(parent); }
};

class Image: public VDOMWidget
{
    Q_OBJECT
public:
    Image(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Image(parent); }
};

class FormPassword: public VDOMWidget
{
    Q_OBJECT
public:
    FormPassword(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormPassword(parent); }
};

class SmartFolderPresentation: public VDOMWidget
{
    Q_OBJECT
public:
    SmartFolderPresentation(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new SmartFolderPresentation(parent); }
};

class VDOMPackage: public VDOMWidget
{
    Q_OBJECT
public:
    VDOMPackage(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new VDOMPackage(parent); }
};

class VDOMDynamicObject: public VDOMWidget
{
    Q_OBJECT
public:
    VDOMDynamicObject(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new VDOMDynamicObject(parent); }
};

class VDOMClass: public VDOMWidget
{
    Q_OBJECT
public:
    VDOMClass(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new VDOMClass(parent); }
};

class FlashAnimation: public VDOMWidget
{
    Q_OBJECT
public:
    FlashAnimation(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FlashAnimation(parent); }
};

class Form: public VDOMWidget
{
    Q_OBJECT
public:
    Form(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Form(parent); }
};

class FormDropdownList: public VDOMWidget
{
    Q_OBJECT
public:
    FormDropdownList(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormDropdownList(parent); }
};

class Tree: public VDOMWidget
{
    Q_OBJECT
public:
    Tree(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Tree(parent); }
};

class AsyncFileUploader: public VDOMWidget
{
    Q_OBJECT
public:
    AsyncFileUploader(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new AsyncFileUploader(parent); }
};

class DBHTMLView: public VDOMWidget
{
    Q_OBJECT
public:
    DBHTMLView(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DBHTMLView(parent); }
};

class Pagination: public VDOMWidget
{
    Q_OBJECT
public:
    Pagination(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Pagination(parent); }
};

class FormDate: public VDOMWidget
{
    Q_OBJECT
public:
    FormDate(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormDate(parent); }
};

class FormTextArea: public VDOMWidget
{
    Q_OBJECT
public:
    FormTextArea(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormTextArea(parent); }
};

class Photogallery: public VDOMWidget
{
    Q_OBJECT
public:
    Photogallery(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Photogallery(parent); }
};

class LanguageSelector: public VDOMWidget
{
    Q_OBJECT
public:
    LanguageSelector(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new LanguageSelector(parent); }
};

class SmartFolderDataContainer: public VDOMWidget
{
    Q_OBJECT
public:
    SmartFolderDataContainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new SmartFolderDataContainer(parent); }
};

class Uploader: public VDOMWidget
{
    Q_OBJECT
public:
    Uploader(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Uploader(parent); }
};

class DialogV2: public VDOMWidget
{
    Q_OBJECT
public:
    DialogV2(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DialogV2(parent); }
};

class FullTextSearch: public VDOMWidget
{
    Q_OBJECT
public:
    FullTextSearch(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FullTextSearch(parent); }
};

class PrintToWebContainer: public VDOMWidget
{
    Q_OBJECT
public:
    PrintToWebContainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new PrintToWebContainer(parent); }
};

class Copy: public VDOMWidget
{
    Q_OBJECT
public:
    Copy(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Copy(parent); }
};

class ListV2: public VDOMWidget
{
    Q_OBJECT
public:
    ListV2(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new ListV2(parent); }
};

class DBSchema: public VDOMWidget
{
    Q_OBJECT
public:
    DBSchema(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DBSchema(parent); }
};

class FormRadiogroup: public VDOMWidget
{
    Q_OBJECT
public:
    FormRadiogroup(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormRadiogroup(parent); }
};

class DatatableV3: public VDOMWidget
{
    Q_OBJECT
public:
    DatatableV3(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DatatableV3(parent); }
};

class Bar: public VDOMWidget
{
    Q_OBJECT
public:
    Bar(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Bar(parent); }
};

class HTMLContainer: public VDOMWidget
{
    Q_OBJECT
public:
    HTMLContainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new HTMLContainer(parent); }
};

class LicenseContainer: public VDOMWidget
{
    Q_OBJECT
public:
    LicenseContainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new LicenseContainer(parent); }
};

class Splitter: public VDOMWidget
{
    Q_OBJECT
public:
    Splitter(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Splitter(parent); }
};

class TableRow: public VDOMWidget
{
    Q_OBJECT
public:
    TableRow(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new TableRow(parent); }
};

class Tabview: public VDOMWidget
{
    Q_OBJECT
public:
    Tabview(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Tabview(parent); }
};

class Button: public VDOMWidget
{
    Q_OBJECT
public:
    Button(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Button(parent); }
};

class List: public VDOMWidget
{
    Q_OBJECT
public:
    List(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new List(parent); }
};

class Timer: public VDOMWidget
{
    Q_OBJECT
public:
    Timer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Timer(parent); }
};

class Flot: public VDOMWidget
{
    Q_OBJECT
public:
    Flot(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Flot(parent); }
};

class Sensitive: public VDOMWidget
{
    Q_OBJECT
public:
    Sensitive(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Sensitive(parent); }
};

class CodeEditor: public VDOMWidget
{
    Q_OBJECT
public:
    CodeEditor(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new CodeEditor(parent); }
};

class Contact: public VDOMWidget
{
    Q_OBJECT
public:
    Contact(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Contact(parent); }
};

class PrintToWebScript: public VDOMWidget
{
    Q_OBJECT
public:
    PrintToWebScript(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new PrintToWebScript(parent); }
};

class FormColorPicker: public VDOMWidget
{
    Q_OBJECT
public:
    FormColorPicker(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new FormColorPicker(parent); }
};

class Menu: public VDOMWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Menu(parent); }
};

class Debug: public VDOMWidget
{
    Q_OBJECT
public:
    Debug(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Debug(parent); }
};

class DesktopSharedModule: public VDOMWidget
{
    Q_OBJECT
public:
    DesktopSharedModule(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new DesktopSharedModule(parent); }
};

class ObjectView: public VDOMWidget
{
    Q_OBJECT
public:
    ObjectView(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new ObjectView(parent); }
};

class MySQLConnector: public VDOMWidget
{
    Q_OBJECT
public:
    MySQLConnector(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new MySQLConnector(parent); }
};

class Richtext: public VDOMWidget
{
    Q_OBJECT
public:
    Richtext(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Richtext(parent); }
};

// end classes

typedef VDOMWidget* (*FactoryFunction)(QWidget*);

static QMap<QString, FactoryFunction> makeFactory()
{
    QMap<QString, FactoryFunction> f;

    // creators
    f["formimage"] = FormImage::create;
    f["printtowebaction"] = PrintToWebAction::create;
    f["formlist"] = FormList::create;
    f["svgbook"] = SVGBook::create;
    f["fullcalendar"] = FullCalendar::create;
    f["hypertext"] = Hypertext::create;
    f["fulltextindex"] = FullTextIndex::create;
    f["progressbar"] = ProgressBar::create;
    f["desktopapplication"] = DesktopApplication::create;
    f["table"] = Table::create;
    f["calendar"] = Calendar::create;
    f["accordeon"] = Accordion::create;
    f["formradiobutton"] = FormRadiobutton::create;
    f["dbtable"] = DatabaseTable::create;
    f["dynobjectview"] = DynamicObjectView::create;
    f["formtext"] = FormText::create;
    f["desktopform"] = DesktopApplicationForm::create;
    f["growl"] = Growl::create;
    f["indexconnector"] = Indexconnector::create;
    f["container"] = Container::create;
    f["formtexteditor"] = FormTextEditor::create;
    f["xmlcontainer"] = XMLContainer::create;
    f["breadcrumbs"] = Breadcrumbs::create;
    f["webdavcontainer"] = WebDAVContainer::create;
    f["formcheckbox"] = FormCheckbox::create;
    f["shortcut"] = Shortcut::create;
    f["connector"] = Connector::create;
    f["tablecell"] = TableCell::create;
    f["desktopscript"] = DesktopApplicationScript::create;
    f["editableresource"] = EditableResource::create;
    f["carousel"] = Carousel::create;
    f["text"] = Text::create;
    f["formbutton"] = FormButton::create;
    f["xmldialog"] = XMLDialog::create;
    f["image"] = Image::create;
    f["formpassword"] = FormPassword::create;
    f["smartfolder"] = SmartFolderPresentation::create;
    f["vdompackage"] = VDOMPackage::create;
    f["dynamicvdom"] = VDOMDynamicObject::create;
    f["vdomclass"] = VDOMClass::create;
    f["flashanimation"] = FlashAnimation::create;
    f["form"] = Form::create;
    f["formdropdown"] = FormDropdownList::create;
    f["tree"] = Tree::create;
    f["uploader_2"] = AsyncFileUploader::create;
    f["dbhtmlview"] = DBHTMLView::create;
    f["pagination"] = Pagination::create;
    f["formdate"] = FormDate::create;
    f["formtextarea"] = FormTextArea::create;
    f["photogallery"] = Photogallery::create;
    f["language_selector"] = LanguageSelector::create;
    f["smartfolderdata"] = SmartFolderDataContainer::create;
    f["uploader"] = Uploader::create;
    f["dialog_2"] = DialogV2::create;
    f["fulltextsearch"] = FullTextSearch::create;
    f["printtowebcontainer"] = PrintToWebContainer::create;
    f["copy"] = Copy::create;
    f["listv2"] = ListV2::create;
    f["dbschema"] = DBSchema::create;
    f["formradiogroup"] = FormRadiogroup::create;
    f["datatable_v3"] = DatatableV3::create;
    f["bar"] = Bar::create;
    f["htmlcontainer"] = HTMLContainer::create;
    f["license"] = LicenseContainer::create;
    f["splitter"] = Splitter::create;
    f["tablerow"] = TableRow::create;
    f["tabview"] = Tabview::create;
    f["button"] = Button::create;
    f["list"] = List::create;
    f["timer"] = Timer::create;
    f["flot"] = Flot::create;
    f["sensitive"] = Sensitive::create;
    f["codeeditor"] = CodeEditor::create;
    f["contact"] = Contact::create;
    f["printtowebscript"] = PrintToWebScript::create;
    f["formcolorpicker"] = FormColorPicker::create;
    f["menu"] = Menu::create;
    f["debug"] = Debug::create;
    f["desktopshared"] = DesktopSharedModule::create;
    f["objectview"] = ObjectView::create;
    f["mysqlconnector"] = MySQLConnector::create;
    f["richtext"] = Richtext::create;
    // end creators

    return f;
}

static QMap<QString, FactoryFunction> factory = makeFactory();

#endif // VDOMCLASSES_H
