import os

types_path = "D:\\dev\\vdomserver1.3\\types"
output_file = "types.xml"
max_types = -1

output = open(output_file, "wb")
output.write("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n")
output.write("<Types>\n")

count = 0

def add_type(fname):
	global count
	if max_types > -1 and count >= max_types:
		return
	f = open(os.path.join(types_path, fname), "rb")
	data = f.read()
	f.close()
	if data.startswith("<?xml"):
		data = data[data.find("<Type>"):]
	output.write(data)
	output.write("\n")
	count += 1

for item in os.walk(types_path):
	files = item[2]
	for fname in files:
		if fname.endswith(".xml"):
			add_type(fname)

output.write("</Types>\n")
output.close()
