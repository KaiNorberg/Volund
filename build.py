import argparse
import subprocess
import os
from sys import platform
import shutil
import glob

def IsLinux():
    return platform == "linux" or platform == "linux2"
def IsWindows():
    return platform == "win32"

PREMAKE_FOLDER = os.path.join("vendor", "premake")

PREMAKE_EXECUTABLE = None
if IsLinux():
    PREMAKE_EXECUTABLE = os.path.join(PREMAKE_FOLDER, "premake5")
elif IsWindows():
    PREMAKE_EXECUTABLE = os.path.join(PREMAKE_FOLDER, "premake5.exe")

DEPLOY_FOLDER = os.path.join("deploy")
DEPLOY_EDITOR_FOLDER = os.path.join(DEPLOY_FOLDER, "Editor")
DEPLOY_EDITOR_DATA_FOLDER = os.path.join(DEPLOY_EDITOR_FOLDER, "data")
DEPLOY_LIB_FOLDER = os.path.join(DEPLOY_FOLDER, "lib")
DEPLOY_INCLUDE_FOLDER = os.path.join(DEPLOY_LIB_FOLDER, "include")

VOLUND_SRC_FOLDER = os.path.join("Volund", "src")
EDITOR_DATA_FOLDER = os.path.join("Editor", "data")

BIN_FOLDER = os.path.join("bin", "Dist_x64")

parser = argparse.ArgumentParser(description="Volund build tools")
parser.add_argument("-pm", "--premake", metavar="ACTION", type=str)
parser.add_argument("-d", "--deploy", action="store_true")
args = parser.parse_args()

def RecursiveCopy(src, dest, extension):
    for path in glob.glob(os.path.join(src, "**", "*." + extension), recursive=True):
        relativeSrc = path.removeprefix(src)
        relativeDest = dest + relativeSrc
        relativeDestDir = os.path.dirname(relativeDest)
        if not (os.path.exists(relativeDestDir)):
            os.makedirs(relativeDestDir)
        shutil.copy(path, relativeDest)
        
def DeployLibLinux():
    print("Not Implemented!")

def DeployLibWin():
    if (os.path.exists(DEPLOY_FOLDER)):
        shutil.rmtree(DEPLOY_FOLDER)
    os.mkdir(DEPLOY_FOLDER)

    os.mkdir(DEPLOY_LIB_FOLDER)
    os.mkdir(DEPLOY_INCLUDE_FOLDER)

    RecursiveCopy(VOLUND_SRC_FOLDER, DEPLOY_INCLUDE_FOLDER, "h")
    shutil.copy(os.path.join(BIN_FOLDER, "Volund.lib"), DEPLOY_LIB_FOLDER)
    shutil.copy(os.path.join(BIN_FOLDER, "Volund.pdb"), DEPLOY_LIB_FOLDER)
    
    os.mkdir(DEPLOY_EDITOR_FOLDER)
    os.mkdir(DEPLOY_EDITOR_DATA_FOLDER)
    RecursiveCopy(EDITOR_DATA_FOLDER, DEPLOY_EDITOR_DATA_FOLDER, "*")
    shutil.copy(os.path.join(BIN_FOLDER, "Editor.exe"), DEPLOY_EDITOR_FOLDER)


def main():
    if (args.premake != None):
        subprocess.call([PREMAKE_EXECUTABLE, args.premake])

    if (args.deploy == True):
        print("Please wait...")
        if IsLinux():
            DeployLibLinux()
        elif IsWindows():
            DeployLibWin()
        print("Done!")
            
if __name__ == "__main__":
    main()