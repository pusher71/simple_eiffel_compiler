import sys
import subprocess
import os
import glob

# Eiffel class
class EiffelClass:
	def __init__(self, eclass_as_txt):
		self.name 			= ''
		self.parents_info 	= []
		self.features 		= []

		self.parse(eclass_as_txt)

	def parse(self, eclass_as_txt):
		eclass_info = eclass_as_txt.split(':')

		self.name = eclass_info[0]

		for parent_info in eclass_info[1].split(')')[:-1]:
			parent_name 		= parent_info.split('(')[0]

			parent_renames 		= parent_info.split('(')[1].split(';')[0].split(',')
			parent_redefines 	= parent_info.split('(')[1].split(';')[1].split(',')
			parent_selects 		= parent_info.split('(')[1].split(';')[2].split(',')

			self.parents_info.append(EiffelParentInfo(parent_name, parent_renames, parent_redefines, parent_selects))

		for feature_info in eclass_info[2].split(','):
			if len(feature_info):
				if feature_info[0] == '#':
					self.features.append(EiffelFeatureInfo(self.name, feature_info[1:], False))
				else:
					self.features.append(EiffelFeatureInfo(self.name, feature_info))

	def to_text(self):
		result = []
		result.append('class ' + self.name)

		if len(self.parents_info):
			result.append('  inherit')
		
			for parent in self.parents_info:
				parent_as_txt = parent.to_text()

				for parent_line in parent_as_txt:
					result.append(parent_line)

		if len(self.features):
			result.append('  feature')

			for feature in self.features:
				feature_as_txt = feature.to_text()

				for feature_line in feature_as_txt:
					result.append(feature_line)

		result.append('end')
	
		return result

class EiffelParentInfo:
	def __init__(self, name, renames, redefines, selects):
		self.name 			= name

		self.renames 	= renames
		self.redefines 	= redefines
		self.selects 	= selects

	def to_text(self):
		result = []
		result.append('    ' + self.name)

		if self.renames[0] != '':
			result.append('    rename')

			for rename in self.renames:
				if rename != self.renames[-1:][0]:
					result.append('      ' + rename + ',')
				else:
					result.append('      ' + rename)

		if self.redefines[0] != '':
			result.append('    redefine')

			for redefine in self.redefines:
				if redefine != self.redefines[-1:][0]:
					result.append('      ' + redefine + ',')
				else:
					result.append('      ' + redefine)

		if self.selects[0] != '':
			result.append('    select')

			for select in self.selects:
				if select != self.selects[-1:][0]:
					result.append('      ' + select + ',')
				else:
					result.append('      ' + select)

		if self.renames[0] != '' or self.redefines[0] != '' or self.selects[0] != '':
			result.append('    end')

		return result;

class EiffelFeatureInfo:
	def __init__(self, class_name, name, is_method = True):
		self.class_name = class_name
		self.name = name
		self.is_method = is_method

	def to_text(self):
		result = []
		result.append('    ' + self.name)

		if self.is_method:
			result.append('    do')
			result.append('      io.put_string(\"' + self.class_name + '::' + self.name + '()%N\")')
			result.append('    end')
		else:
			result.append(': INTEGER')

		return result

# Read file
with open(sys.argv[1], 'r') as f:
	main_file_data = f.read()

# Parse file for getting Eiffel classes and MAIN code
main_locals 	= []
main_code 		= []
user_classes 	= []

read_code = 0

for line in main_file_data.splitlines():
	if line == "##":
		read_code += 1

	elif line != "":
		if read_code == 0:
			main_locals.append(line)

		elif read_code == 1:
			main_code.append(line)

		elif read_code == 2:
			user_classes.append(EiffelClass(line))

# Save to output gotten Eiffel classes
with open('output.er', 'w') as output_file:
	output_file.write('-- main.e')
	output_file.write('\n')
	output_file.write('class MAIN')
	output_file.write('\n')
	output_file.write('create make')
	output_file.write('\n')
	output_file.write('feature')
	output_file.write('\n')
	output_file.write('make')
	output_file.write('\n')

	if len(main_locals):
		output_file.write('local')
		output_file.write('\n')

		for local in main_locals:
			output_file.write(local)
			output_file.write('\n')

	output_file.write('do')
	output_file.write('\n')
	for code_line in main_code:
		output_file.write(code_line)
		output_file.write('\n')
	output_file.write('end')
	output_file.write('\n')

	output_file.write('end')
	output_file.write('\n')
	
	output_file.write('-- EOF')	
	output_file.write('\n')
	output_file.write('\n')

	for eclass in user_classes:
		eclass_def_txt = eclass.to_text()

		output_file.write('-- ' + eclass.name + '.e')	
		output_file.write('\n')
		for eclass_def_line in eclass_def_txt:
			output_file.write(eclass_def_line)
			output_file.write('\n')
		output_file.write('-- EOF')	
		output_file.write('\n')
		output_file.write('\n')
