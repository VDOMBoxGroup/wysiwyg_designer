import os, string

types_file = "types.txt"
output_file = "vdomtypesplugin\\vdomclasses.h"

start = """#ifndef VDOMCLASSES_H
#define VDOMCLASSES_H

#include "vdomclassfactory.h"
#include <QMap>
#include <QString>

"""

end = """static QMap<QString, FactoryFunction> factory = makeFactory();

#endif // VDOMCLASSES_H
"""

class_templ = """class {class_name}: public VDOMWidget
{{
    Q_OBJECT
public:
    {class_name}(QWidget *parent) : VDOMWidget(parent) {{}}
    static VDOMWidget* create(QWidget *parent) {{ return new {class_name}(parent); }}
}};

"""

factory_start = """typedef VDOMWidget* (*FactoryFunction)(QWidget*);

static QMap<QString, FactoryFunction> makeFactory()
{
    QMap<QString, FactoryFunction> f;

    // creators
"""

factory_end = """    // end creators

    return f;
}

"""

factory_templ = """    f["{type_name}"] = {class_name}::create;
"""

inp = open(types_file, "r")
outp = open(output_file, "w")

def read_types(f):
	return [i for i in map(string.strip, f.readlines()) if i]

def write_start(f):
	f.write(start)

def write_end(f):
	f.write(end)

def write_class(f, class_name):
	f.write(class_templ.format(class_name=class_name))

def write_classes(f, class_names):
	f.write('// classes\n\n')
	for class_name in class_names:
		write_class(f, class_name)
	f.write('// end classes\n\n')

def write_factory(f, types):
	f.write(factory_start)
	for type_name in types:
		f.write(factory_templ.format(type_name=type_name, class_name=type_name.capitalize()))
	f.write(factory_end)


types = read_types(inp)
write_start(outp)
write_classes(outp, map(string.capitalize, types))
write_factory(outp, types)
write_end(outp)


inp.close()
outp.close()
