#include <QtGui>
#include <QtWebKit/QWebView>
#include <QtSvg/QSvgWidget>
#include <QLabel>
#include <QTableWidget>
#include <QFrame>
#include "vdomtypeswidget.h"
#include "util.h"

typedef QWidget* (*WidgetCreatorPtr)(QWidget *parent, const WItem &w);

static QMap<QString, WidgetCreatorPtr> MakeWidgetCreators();

static QMap<QString, WidgetCreatorPtr> widgetCreators = MakeWidgetCreators();

VdomTypesWidget::VdomTypesWidget(QWidget *parent)
    : QWidget(parent)
{
    baseZindex = globalZindex = 0;
}

void VdomTypesWidget::setWysiwyg(const WItem &w)
{
    //qDebug("Object \'%s\' set wysiwyg \'%s\'", objectName().toLatin1().constData(), w.name.toLatin1().constData());
    wysiwyg = w;
    baseZindex = w.intAttr("zindex");
    removeChildWidgets();
    createChildWidgets(this, wysiwyg);
    update();
}

void VdomTypesWidget::updateWysiwyg()
{
    setWysiwyg(wysiwyg);
}

void VdomTypesWidget::removeChild(QWidget *p)
{
    if (!p)
        return;
    while (QWidget *w = p->findChild<QWidget*>())
        delete w;
    delete p;
}

void VdomTypesWidget::removeChildWidgets()
{
    QObjectList ch = children();
    for (QObjectList::iterator i=ch.begin(); i!=ch.end(); i++) {
        VdomTypesWidget *t = qobject_cast<VdomTypesWidget*>(*i);
        if (!t)
            removeChild(qobject_cast<QWidget*>(*i));
    }
}

void VdomTypesWidget::createChildWidgets(QWidget *parent, const WItem &w)
{
    QMap<QString, WidgetCreatorPtr>::iterator i = widgetCreators.find(w.name);
    if (i == widgetCreators.end()) {
        qDebug("Unknown WYSIWYG tag \'%s\'", w.name.toLatin1().constData());
        return;
    }
    //qDebug("Create \'%s\'", w.name.toLatin1().constData());
    QWidget *child = (*i.value())(parent, w);
    for (QList<WItem>::const_iterator i=w.child.begin(); i!=w.child.end(); i++)
        createChildWidgets(child, *i);
}

void VdomTypesWidget::paintEvent(QPaintEvent*)
{
    if (wysiwyg.isEmpty()) {
        QPainter painter(this);
        painter.setPen(Qt::DashLine);
        painter.drawRect(0, 0, width()-1, height()-1);
        painter.drawText(2, 12, vdomType->displayName + "::" + objectName());
        QPixmap p = vdomType->icon.pixmap(100);
        painter.drawPixmap((rect().width() - p.width()) / 2, (rect().height() - p.height()) / 2, p);
    }
}

void VdomTypesWidget::updateZindex()
{
    QObjectList ch = children();
    for (QObjectList::iterator i=ch.begin(); i!=ch.end(); i++) {
        VdomTypesWidget *t = qobject_cast<VdomTypesWidget*>(*i);
        if (t) {
            t->globalZindex = t->baseZindex + globalZindex + 1;
            t->updateZindex();
        }
    }
}

// === widget creators

void SetGeometry(QWidget *v, const WItem &w, QWidget *parent, bool container=false)
{
    int top = w.intAttr("top"), left = w.intAttr("left"),
            width = w.intAttr("width"), height = w.intAttr("height");
    if (container && !w.objectName().isEmpty())
        top = left = 0;
    if (!height)
        height = parent->height() - top;
    if (!width)
        width = parent->width() - left;
    //qDebug("%s geometry %d %d %d %d", w.name.toLatin1().constData(), left, top, width, height);
    v->setGeometry(left, top, width, height);
}

void AddToTable(QWidget *w, QTableWidget *t)
{
    QPalette widgetPalette = w->palette();
    QPalette tablePalette = t->palette();
    widgetPalette.setColor(QPalette::Window, tablePalette.color(QPalette::Window));
    widgetPalette.setColor(QPalette::Base, tablePalette.color(QPalette::Window));
    w->setPalette(widgetPalette);
    t->setCellWidget(t->rowCount() - 1, t->property("current_cell").toInt(), w);
}

QWidget* MakeContainer(QWidget *parent, const WItem &w)
{
    QTableWidget *table = qobject_cast<QTableWidget*>(parent);
    QFrame *v = new QFrame(table ? NULL : parent);
    SetGeometry(v, w, parent, true);
    delete v->layout();
    QString color = w.strAttr("backgroundcolor");
    if (!color.isEmpty()) {
        QPalette p = v->palette();
        p.setColor(QPalette::Window, ParseColor(color));
        v->setAutoFillBackground(true);
        v->setPalette(p);
    }
    color = w.strAttr("bordercolor");
    if (!color.isEmpty()) {
        QPalette p = v->palette();
        p.setColor(QPalette::WindowText, ParseColor(color));
        v->setPalette(p);
        v->setFrameShadow(QFrame::Plain);
        v->setFrameShape(QFrame::Box);
    }
    v->setVisible(true);
    if (table)
        AddToTable(v, table);
    return v;
}

QWidget* MakeText(QWidget *parent, const WItem &w)
{
    QTableWidget *table = qobject_cast<QTableWidget*>(parent);
    QLabel *l = new QLabel(table ? NULL : parent);

    SetGeometry(l, w, parent);

    Qt::Alignment a = Qt::AlignLeft;
    QString align = w.strAttr("textalign");
    if (align == "center")
        a = Qt::AlignHCenter;
    else if (align == "right")
        a = Qt::AlignRight;
    l->setAlignment(a);

    QString fontFamily = w.strAttr("fontfamily");
    if (fontFamily.isEmpty())
        fontFamily = "Tahoma";
    int fontSize = w.intAttr("fontsize");
    if (!fontSize)
        fontSize = 12;
    int fontWeight = QFont::Normal;
    if (w.strAttr("fontweight") == "bold")
        fontWeight = QFont::Bold;

    QFont f(fontFamily, fontSize, fontWeight, (w.strAttr("fontstyle") == "italic"));
    f.setUnderline(w.strAttr("textdecoration") == "underline");
    l->setFont(f);

    QString color = w.strAttr("color");
    if (!color.isEmpty()) {
        QPalette p = l->palette();
        p.setColor(QPalette::WindowText, ParseColor(color));
        p.setColor(QPalette::Text, ParseColor(color));
        l->setPalette(p);
    }

    l->setText(w.value);
    if (!w.value.isEmpty())
        l->setVisible(true);
    l->setAttribute(Qt::WA_TranslucentBackground);
    l->setAutoFillBackground(false);

    if (table)
        AddToTable(l, table);
    return l;
}

QWidget* MakeWebView(QWidget *parent, const WItem &w)
{
    QTableWidget *table = qobject_cast<QTableWidget*>(parent);
    QWebView *v = new QWebView(table ? NULL : parent);
    SetGeometry(v, w, parent);
    v->setHtml(w.value);
    if (!w.value.isEmpty())
        v->setVisible(true);
    if (table)
        AddToTable(v, table);
    return v;
}

QWidget* MakeSvg(QWidget *parent, const WItem &w)
{
    QTableWidget *table = qobject_cast<QTableWidget*>(parent);
    QSvgWidget *v = new QSvgWidget(table ? NULL : parent);
    QByteArray a;
    a.append("<svg xmlns:xlink=\"http://www.w3.org/1999/xlink\">");
    QString svg = w.value;
    svg.replace("href", "xlink:href");
    a.append(svg);
    a.append("</svg>");
    v->setVisible(true);
    v->load(a);
    QRect r = parent->geometry();
    QSize s = v->sizeHint();
    if (s.width() && s.height()) {
        v->setGeometry(r.x() + (r.width() - s.width()) / 2,
                       r.y() + (r.height() - s.height()) / 2,
                       s.width(),
                       s.height());
    } else {
        v->setGeometry(parent->geometry());
    }
    if (table)
        AddToTable(v, table);
    //qDebug("SVG %s", svg.toLatin1().constData());
    //qDebug("SVG size %dx%d", v->sizeHint().width(), v->sizeHint().height());
    //qDebug("SVG geometry %d %d %d %d", v->geometry().left(), v->geometry().top(), v->geometry().width(), v->geometry().height());
    return v;
}

QWidget* MakeTable(QWidget *parent, const WItem &w)
{
    QTableWidget *v = new QTableWidget(parent);
    SetGeometry(v, w, parent);
    QString color = w.strAttr("backgroundcolor");
    if (!color.isEmpty()) {
        QPalette p = v->palette();
        p.setColor(QPalette::Window, ParseColor(color));
        v->setPalette(p);
    }
    v->setVisible(true);
    v->horizontalHeader()->hide();
    v->verticalHeader()->hide();
    return v;
}

QWidget* MakeRow(QWidget *parent, const WItem &w)
{
    QTableWidget *v = qobject_cast<QTableWidget*>(parent);
    if (!v) {
        qDebug("Incorrect outer tag for <row>");
        return parent;
    }
    v->insertRow(v->rowCount());
    int height = w.intAttr("height");
    if (height)
        v->setRowHeight(v->rowCount() - 1, height);
    v->setProperty("current_cell", QVariant(-1));
    return parent;
}

QWidget* MakeCell(QWidget *parent, const WItem &w)
{
    QTableWidget *v = qobject_cast<QTableWidget*>(parent);
    if (!v) {
        qDebug("Incorrect outer tag for <cell>");
        return parent;
    } else if (!v->rowCount()) {
        qDebug("Table has no rows");
        return parent;
    }
    int currentCell = v->property("current_cell").toInt() + 1;
    if (currentCell >= v->columnCount())
        v->insertColumn(v->columnCount());
    v->setProperty("current_cell", QVariant(currentCell));
    int width = w.intAttr("width");
    if (width)
        v->setColumnWidth(currentCell, width);
    int colspan = w.intAttr("colspan");
    if (!colspan)
        colspan = 1;
    int rowspan = w.intAttr("rowspan");
    if (!rowspan)
        rowspan = 1;
    if (rowspan != 1 || colspan != 1)
        v->setSpan(v->rowCount() - 1, currentCell, rowspan, colspan);

    return parent;
}

static QMap<QString, WidgetCreatorPtr> MakeWidgetCreators()
{
    QMap<QString, WidgetCreatorPtr> ret;
    ret["container"] = MakeContainer;
    ret["text"] = MakeText;
    ret["htmltext"] = MakeWebView;
    ret["svg"] = MakeSvg;
    ret["table"] = MakeTable;
    ret["row"] = MakeRow;
    ret["cell"] = MakeCell;
    return ret;
}
