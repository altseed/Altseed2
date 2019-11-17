import os
import re
import subprocess

def cd(path):
    os.chdir(os.path.abspath(path))

class CurrentDir:
    def __init__(self, path):
        self.prev = os.getcwd()
        self.path = path

    def __enter__(self):
        cd(self.path)
        return self

    def __exit__(self, type, value, traceback):
        cd(self.prev)

def update_submodule():
    subprocess.call(["git", "submodule", "update"])

    if not os.path.exists(".gitmodules"):
        return
    
    with open(".gitmodules", "r") as file:
        pattern = re.compile(r"\tpath = (.*)")
        for line in file.readlines():
            result = pattern.match(line)
            if result:
                path = result.group(1)
                print(path)

                with CurrentDir(path):
                    update_submodule()

cd(os.path.dirname(__file__) + "/..")

update_submodule()
