import sys
import os

import glob
import chardet

os.chdir(os.path.dirname(__file__))

root = "../core/src"
if len(sys.argv) == 2:
    root = sys.argv[1]
if root[(len(root) - 1):len(root)] != "/":
    root += "/"

extensions = [ "cpp", "h" ]
for ext in extensions:
    for path in glob.glob(root + "**/*." + ext, recursive=True):
        text = ""
        with open(path, mode="rb") as ifile:
            buffer = ifile.read()
            encode = chardet.detect(buffer)["encoding"]
            if encode == "utf-8-sig":
                continue

            try:
                text = buffer.decode(encode)
            except UnicodeDecodeError as e:
                print("decode error: " + path)
                print(e.reason)
                print("(ditect encode: " + encode + ")")
                continue
        
        with open(path, mode="wt", encoding="utf-8-sig") as ofile:
            ofile.write(text)



