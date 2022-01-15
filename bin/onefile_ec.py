import sys
import subprocess
import os
import glob

# Read file
with open(sys.argv[1], 'r') as f:
	main_file_data = f.read()

# Divide content of file into files
files_data = []

file_data = []
for line in main_file_data.splitlines():
	if line == "-- EOF":
		files_data.append(file_data)
		file_data = []

	elif line != "":
		file_data.append(line)

# Save files
for file_data in files_data:
	with open(file_data[0][3:], 'w') as fi:
		for line in file_data[1:]:
			fi.write(line + "\n")

# Run Eiffel compiler
mainfile_name = files_data[0][0][3:]
exe_name = os.path.splitext(mainfile_name)[0]

subprocess.run(["ec", files_data[0][0][3:]])

# Check if executable was produced
if os.path.isfile("./" + exe_name):
	# Run executable
	subprocess.run(["chmod", "+x", exe_name])
	subprocess.run(["./" + exe_name])

	# Clear created files
	subprocess.run(["rm", "-rf", exe_name])

	subprocess.run(["rm", "-rf", "EIFGENs"])
	for file in glob.glob("*.e") + glob.glob("*.ecf"):
		subprocess.run(["rm", file])
