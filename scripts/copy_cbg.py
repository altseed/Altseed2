import os, shutil, ntpath, glob

# move to source directory
os.chdir(os.path.dirname(os.path.abspath(__file__)))

cbgDir = './cbg'

def createIfNotFound(dir):
    if os.path.exists(dir):
        for path in glob.glob(dir + '/*.py'):
            os.remove(path)
            print('removed ' + path)
    else:
        os.mkdir(dir)
        print('Created directory ' + dir)
    

createIfNotFound(cbgDir)

def copyFile(path, dir):
    oPath = '{}/{}'.format(dir, ntpath.split(path)[1])
    shutil.copy(path, oPath)
    print('copied file from {} to {}'.format(path, oPath))


for path in glob.glob('../../CBG/cbg/*.py'):
    copyFile(path, cbgDir)
