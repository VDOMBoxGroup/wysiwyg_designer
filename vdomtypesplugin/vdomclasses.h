#ifndef VDOMCLASSES_H
#define VDOMCLASSES_H

#include "vdomclassfactory.h"
#include <QMap>
#include <QString>

// classes

class Accordeon: public VDOMWidget
{
    Q_OBJECT
public:
    Accordeon(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Accordeon(parent); }
};

class Bar: public VDOMWidget
{
    Q_OBJECT
public:
    Bar(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Bar(parent); }
};

class Breadcrumbs: public VDOMWidget
{
    Q_OBJECT
public:
    Breadcrumbs(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Breadcrumbs(parent); }
};

class Button: public VDOMWidget
{
    Q_OBJECT
public:
    Button(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Button(parent); }
};

class Calendar: public VDOMWidget
{
    Q_OBJECT
public:
    Calendar(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Calendar(parent); }
};

class Carousel: public VDOMWidget
{
    Q_OBJECT
public:
    Carousel(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Carousel(parent); }
};

class Codeeditor: public VDOMWidget
{
    Q_OBJECT
public:
    Codeeditor(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Codeeditor(parent); }
};

class Connector: public VDOMWidget
{
    Q_OBJECT
public:
    Connector(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Connector(parent); }
};

class Contact: public VDOMWidget
{
    Q_OBJECT
public:
    Contact(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Contact(parent); }
};

class Container: public VDOMWidget
{
    Q_OBJECT
public:
    Container(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Container(parent); }
};

class Copy: public VDOMWidget
{
    Q_OBJECT
public:
    Copy(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Copy(parent); }
};

class Datatable_v3: public VDOMWidget
{
    Q_OBJECT
public:
    Datatable_v3(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Datatable_v3(parent); }
};

class Dbhtmlview: public VDOMWidget
{
    Q_OBJECT
public:
    Dbhtmlview(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Dbhtmlview(parent); }
};

class Dbschema: public VDOMWidget
{
    Q_OBJECT
public:
    Dbschema(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Dbschema(parent); }
};

class Dbtable: public VDOMWidget
{
    Q_OBJECT
public:
    Dbtable(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Dbtable(parent); }
};

class Debug: public VDOMWidget
{
    Q_OBJECT
public:
    Debug(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Debug(parent); }
};

class Desktopapplication: public VDOMWidget
{
    Q_OBJECT
public:
    Desktopapplication(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Desktopapplication(parent); }
};

class Desktopform: public VDOMWidget
{
    Q_OBJECT
public:
    Desktopform(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Desktopform(parent); }
};

class Desktopscript: public VDOMWidget
{
    Q_OBJECT
public:
    Desktopscript(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Desktopscript(parent); }
};

class Desktopshared: public VDOMWidget
{
    Q_OBJECT
public:
    Desktopshared(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Desktopshared(parent); }
};

class Dialog_2: public VDOMWidget
{
    Q_OBJECT
public:
    Dialog_2(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Dialog_2(parent); }
};

class Dynamicvdom: public VDOMWidget
{
    Q_OBJECT
public:
    Dynamicvdom(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Dynamicvdom(parent); }
};

class Dynobjectview: public VDOMWidget
{
    Q_OBJECT
public:
    Dynobjectview(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Dynobjectview(parent); }
};

class Editableresource: public VDOMWidget
{
    Q_OBJECT
public:
    Editableresource(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Editableresource(parent); }
};

class Flashanimation: public VDOMWidget
{
    Q_OBJECT
public:
    Flashanimation(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Flashanimation(parent); }
};

class Flot: public VDOMWidget
{
    Q_OBJECT
public:
    Flot(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Flot(parent); }
};

class Form: public VDOMWidget
{
    Q_OBJECT
public:
    Form(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Form(parent); }
};

class Formbutton: public VDOMWidget
{
    Q_OBJECT
public:
    Formbutton(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formbutton(parent); }
};

class Formcheckbox: public VDOMWidget
{
    Q_OBJECT
public:
    Formcheckbox(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formcheckbox(parent); }
};

class Formcolorpicker: public VDOMWidget
{
    Q_OBJECT
public:
    Formcolorpicker(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formcolorpicker(parent); }
};

class Formdate: public VDOMWidget
{
    Q_OBJECT
public:
    Formdate(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formdate(parent); }
};

class Formdropdown: public VDOMWidget
{
    Q_OBJECT
public:
    Formdropdown(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formdropdown(parent); }
};

class Formimage: public VDOMWidget
{
    Q_OBJECT
public:
    Formimage(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formimage(parent); }
};

class Formlist: public VDOMWidget
{
    Q_OBJECT
public:
    Formlist(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formlist(parent); }
};

class Formpassword: public VDOMWidget
{
    Q_OBJECT
public:
    Formpassword(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formpassword(parent); }
};

class Formradiobutton: public VDOMWidget
{
    Q_OBJECT
public:
    Formradiobutton(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formradiobutton(parent); }
};

class Formradiogroup: public VDOMWidget
{
    Q_OBJECT
public:
    Formradiogroup(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formradiogroup(parent); }
};

class Formtext: public VDOMWidget
{
    Q_OBJECT
public:
    Formtext(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formtext(parent); }
};

class Formtextarea: public VDOMWidget
{
    Q_OBJECT
public:
    Formtextarea(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formtextarea(parent); }
};

class Formtexteditor: public VDOMWidget
{
    Q_OBJECT
public:
    Formtexteditor(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Formtexteditor(parent); }
};

class Fullcalendar: public VDOMWidget
{
    Q_OBJECT
public:
    Fullcalendar(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Fullcalendar(parent); }
};

class Fulltextindex: public VDOMWidget
{
    Q_OBJECT
public:
    Fulltextindex(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Fulltextindex(parent); }
};

class Fulltextsearch: public VDOMWidget
{
    Q_OBJECT
public:
    Fulltextsearch(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Fulltextsearch(parent); }
};

class Growl: public VDOMWidget
{
    Q_OBJECT
public:
    Growl(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Growl(parent); }
};

class Htmlcontainer: public VDOMWidget
{
    Q_OBJECT
public:
    Htmlcontainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Htmlcontainer(parent); }
};

class Hypertext: public VDOMWidget
{
    Q_OBJECT
public:
    Hypertext(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Hypertext(parent); }
};

class Image: public VDOMWidget
{
    Q_OBJECT
public:
    Image(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Image(parent); }
};

class Indexconnector: public VDOMWidget
{
    Q_OBJECT
public:
    Indexconnector(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Indexconnector(parent); }
};

class Language_selector: public VDOMWidget
{
    Q_OBJECT
public:
    Language_selector(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Language_selector(parent); }
};

class License: public VDOMWidget
{
    Q_OBJECT
public:
    License(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new License(parent); }
};

class List: public VDOMWidget
{
    Q_OBJECT
public:
    List(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new List(parent); }
};

class Listv2: public VDOMWidget
{
    Q_OBJECT
public:
    Listv2(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Listv2(parent); }
};

class Menu: public VDOMWidget
{
    Q_OBJECT
public:
    Menu(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Menu(parent); }
};

class Mysqlconnector: public VDOMWidget
{
    Q_OBJECT
public:
    Mysqlconnector(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Mysqlconnector(parent); }
};

class Objectview: public VDOMWidget
{
    Q_OBJECT
public:
    Objectview(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Objectview(parent); }
};

class Pagination: public VDOMWidget
{
    Q_OBJECT
public:
    Pagination(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Pagination(parent); }
};

class Photogallery: public VDOMWidget
{
    Q_OBJECT
public:
    Photogallery(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Photogallery(parent); }
};

class Printtowebaction: public VDOMWidget
{
    Q_OBJECT
public:
    Printtowebaction(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Printtowebaction(parent); }
};

class Printtowebcontainer: public VDOMWidget
{
    Q_OBJECT
public:
    Printtowebcontainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Printtowebcontainer(parent); }
};

class Printtowebscript: public VDOMWidget
{
    Q_OBJECT
public:
    Printtowebscript(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Printtowebscript(parent); }
};

class Progressbar: public VDOMWidget
{
    Q_OBJECT
public:
    Progressbar(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Progressbar(parent); }
};

class Richtext: public VDOMWidget
{
    Q_OBJECT
public:
    Richtext(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Richtext(parent); }
};

class Sensitive: public VDOMWidget
{
    Q_OBJECT
public:
    Sensitive(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Sensitive(parent); }
};

class Shortcut: public VDOMWidget
{
    Q_OBJECT
public:
    Shortcut(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Shortcut(parent); }
};

class Smartfolder: public VDOMWidget
{
    Q_OBJECT
public:
    Smartfolder(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Smartfolder(parent); }
};

class Smartfolderdata: public VDOMWidget
{
    Q_OBJECT
public:
    Smartfolderdata(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Smartfolderdata(parent); }
};

class Splitter: public VDOMWidget
{
    Q_OBJECT
public:
    Splitter(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Splitter(parent); }
};

class Svgbook: public VDOMWidget
{
    Q_OBJECT
public:
    Svgbook(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Svgbook(parent); }
};

class Table: public VDOMWidget
{
    Q_OBJECT
public:
    Table(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Table(parent); }
};

class Tablecell: public VDOMWidget
{
    Q_OBJECT
public:
    Tablecell(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Tablecell(parent); }
};

class Tablerow: public VDOMWidget
{
    Q_OBJECT
public:
    Tablerow(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Tablerow(parent); }
};

class Tabview: public VDOMWidget
{
    Q_OBJECT
public:
    Tabview(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Tabview(parent); }
};

class Text: public VDOMWidget
{
    Q_OBJECT
public:
    Text(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Text(parent); }
};

class Timer: public VDOMWidget
{
    Q_OBJECT
public:
    Timer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Timer(parent); }
};

class Tree: public VDOMWidget
{
    Q_OBJECT
public:
    Tree(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Tree(parent); }
};

class Uploader: public VDOMWidget
{
    Q_OBJECT
public:
    Uploader(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Uploader(parent); }
};

class Uploader_2: public VDOMWidget
{
    Q_OBJECT
public:
    Uploader_2(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Uploader_2(parent); }
};

class Vdomclass: public VDOMWidget
{
    Q_OBJECT
public:
    Vdomclass(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Vdomclass(parent); }
};

class Vdompackage: public VDOMWidget
{
    Q_OBJECT
public:
    Vdompackage(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Vdompackage(parent); }
};

class Webdavcontainer: public VDOMWidget
{
    Q_OBJECT
public:
    Webdavcontainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Webdavcontainer(parent); }
};

class Xmlcontainer: public VDOMWidget
{
    Q_OBJECT
public:
    Xmlcontainer(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Xmlcontainer(parent); }
};

class Xmldialog: public VDOMWidget
{
    Q_OBJECT
public:
    Xmldialog(QWidget *parent) : VDOMWidget(parent) {}
    static VDOMWidget* create(QWidget *parent) { return new Xmldialog(parent); }
};

// end classes

typedef VDOMWidget* (*FactoryFunction)(QWidget*);

static QMap<QString, FactoryFunction> makeFactory()
{
    QMap<QString, FactoryFunction> f;

    // creators
    f["accordeon"] = Accordeon::create;
    f["bar"] = Bar::create;
    f["breadcrumbs"] = Breadcrumbs::create;
    f["button"] = Button::create;
    f["calendar"] = Calendar::create;
    f["carousel"] = Carousel::create;
    f["codeeditor"] = Codeeditor::create;
    f["connector"] = Connector::create;
    f["contact"] = Contact::create;
    f["container"] = Container::create;
    f["copy"] = Copy::create;
    f["datatable_v3"] = Datatable_v3::create;
    f["dbhtmlview"] = Dbhtmlview::create;
    f["dbschema"] = Dbschema::create;
    f["dbtable"] = Dbtable::create;
    f["debug"] = Debug::create;
    f["desktopapplication"] = Desktopapplication::create;
    f["desktopform"] = Desktopform::create;
    f["desktopscript"] = Desktopscript::create;
    f["desktopshared"] = Desktopshared::create;
    f["dialog_2"] = Dialog_2::create;
    f["dynamicvdom"] = Dynamicvdom::create;
    f["dynobjectview"] = Dynobjectview::create;
    f["editableresource"] = Editableresource::create;
    f["flashanimation"] = Flashanimation::create;
    f["flot"] = Flot::create;
    f["form"] = Form::create;
    f["formbutton"] = Formbutton::create;
    f["formcheckbox"] = Formcheckbox::create;
    f["formcolorpicker"] = Formcolorpicker::create;
    f["formdate"] = Formdate::create;
    f["formdropdown"] = Formdropdown::create;
    f["formimage"] = Formimage::create;
    f["formlist"] = Formlist::create;
    f["formpassword"] = Formpassword::create;
    f["formradiobutton"] = Formradiobutton::create;
    f["formradiogroup"] = Formradiogroup::create;
    f["formtext"] = Formtext::create;
    f["formtextarea"] = Formtextarea::create;
    f["formtexteditor"] = Formtexteditor::create;
    f["fullcalendar"] = Fullcalendar::create;
    f["fulltextindex"] = Fulltextindex::create;
    f["fulltextsearch"] = Fulltextsearch::create;
    f["growl"] = Growl::create;
    f["htmlcontainer"] = Htmlcontainer::create;
    f["hypertext"] = Hypertext::create;
    f["image"] = Image::create;
    f["indexconnector"] = Indexconnector::create;
    f["language_selector"] = Language_selector::create;
    f["license"] = License::create;
    f["list"] = List::create;
    f["listv2"] = Listv2::create;
    f["menu"] = Menu::create;
    f["mysqlconnector"] = Mysqlconnector::create;
    f["objectview"] = Objectview::create;
    f["pagination"] = Pagination::create;
    f["photogallery"] = Photogallery::create;
    f["printtowebaction"] = Printtowebaction::create;
    f["printtowebcontainer"] = Printtowebcontainer::create;
    f["printtowebscript"] = Printtowebscript::create;
    f["progressbar"] = Progressbar::create;
    f["richtext"] = Richtext::create;
    f["sensitive"] = Sensitive::create;
    f["shortcut"] = Shortcut::create;
    f["smartfolder"] = Smartfolder::create;
    f["smartfolderdata"] = Smartfolderdata::create;
    f["splitter"] = Splitter::create;
    f["svgbook"] = Svgbook::create;
    f["table"] = Table::create;
    f["tablecell"] = Tablecell::create;
    f["tablerow"] = Tablerow::create;
    f["tabview"] = Tabview::create;
    f["text"] = Text::create;
    f["timer"] = Timer::create;
    f["tree"] = Tree::create;
    f["uploader"] = Uploader::create;
    f["uploader_2"] = Uploader_2::create;
    f["vdomclass"] = Vdomclass::create;
    f["vdompackage"] = Vdompackage::create;
    f["webdavcontainer"] = Webdavcontainer::create;
    f["xmlcontainer"] = Xmlcontainer::create;
    f["xmldialog"] = Xmldialog::create;
    // end creators

    return f;
}

static QMap<QString, FactoryFunction> factory = makeFactory();

#endif // VDOMCLASSES_H
