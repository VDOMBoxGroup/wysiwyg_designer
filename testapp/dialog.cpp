#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    editor.initialize(this);
    editor.setContent();

    ui->v1->addWidget(editor.widgetBox());
    ui->v2->addWidget(editor.form());
    ui->l2->addWidget(editor.objectInspector());
    ui->l2->addWidget(editor.propertyEditor());

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
}

Dialog::~Dialog()
{
    delete ui;
}
