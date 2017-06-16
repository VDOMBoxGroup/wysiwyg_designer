#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

//"          <Attribute Name=\"htmlcode\"><![CDATA[<TABLE width=\"100%\" height=\"90%\" style=\"border:1px solid #d7dce5;padding:21px 19px;margin-bottom:20px\"><tr><td></td></tr></table>]]]]><![CDATA[>]]></Attribute>"

static const QString content = "<CONTAINER name=\"container2\" top=\"50\" height=\"246\" width=\"461\" left=\"50\">"
"        <BUTTON name=\"button\" top=\"25\" left=\"245\" width=\"100\" height=\"100\" disabledimg=\"D:/Scan.jpg\"/>"
"        <HYPERTEXT name=\"cadre2\" zindex=\"10\" top=\"68\" height=\"108\" width=\"444\" overflow=\"1\" left=\"9\">"
"          <Attribute Name=\"htmlcode\">123</Attribute>"
"        </HYPERTEXT>"
"        <IMAGE name=\"image1\" top=\"84\" value=\"9bf9e53c-cfc8-4ea7-a14c-12481ab87390\" height=\"68\" left=\"18\" width=\"161\"/>"
"        <TEXT name=\"text1\" zindex=\"10\" top=\"106\" value=\"Chargement ....\" width=\"244\" fontsize=\"25\" color=\"A9DB44\" left=\"192\">"
"          <Attribute Name=\"fontfamily\"><![CDATA[\"Arial Black\", \"Helvetica CY\", \"avant garde\", \"Nimbus Sans L\", sans-serif]]></Attribute>"
"        </TEXT>"
"      </CONTAINER>";

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

bool Dialog::init()
{
    editor.initialize(this);
    editor.setContent();

    ui->v1->addWidget(editor.widgetBox());
    ui->v2->addWidget(editor.form());
    ui->l2->addWidget(editor.objectInspector());
    ui->l2->addWidget(editor.propertyEditor());

    connect(&editor, SIGNAL(modelChanged()), this, SLOT(onChanged()));

//    connect(&editor, SIGNAL(attributeChanged(const QObject&, const QString&, const QVariant&)),
//            this, SLOT(onAttrChanged(const QObject&, const QString&, const QVariant&)));

//    QScriptEngine engine;
//    QObject *designer = new Designer();
//    QScriptValue designerValue = engine.newQObject(designer);
//    QScriptValue parentValue = engine.newQObject(this);
//    engine.globalObject().setProperty("designer", designerValue);
//    engine.globalObject().setProperty("parent", parentValue);
//    QString code = "designer.initialize(parent); var x = designer.widgetBox(); print(x.objectName);";
//    QScriptValue ret = engine.evaluate(code);
//    QString s = ret.toString();
//    int i;
//    i = 0;
    return true;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onChanged()
{
    setContent();
}

void Dialog::onAttrChanged(const QObject &/*object*/, const QString &/*name*/, const QVariant &/*value*/)
{
    //setContent();
}

void Dialog::setContent()
{
    QStringList r, e;
    QString data = editor.getContent(r, e);
    QString errors = e.join("\n");
    if (!errors.isEmpty()) {
        data = errors;
        ui->text->setTextColor(Qt::red);
    } else
        ui->text->setTextColor(Qt::black);
//        errors = "Errors:\n" + errors + "\n";
//    QString resources = r.join("\n");
//    if (!resources.isEmpty())
//        resources = "Resources:\n" + resources;
    //ui->text2->setText(errors + resources);
    ui->text->setText(data);
}
