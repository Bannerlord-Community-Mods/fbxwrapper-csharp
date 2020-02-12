# FBX MENAGER WRAPPER (WIP)

## Visual Studio 2017

- Requires installation of FBX SDK 2019.2, then copy manually all the different versions of "libfbxsdk.lib" in the folder "FbxWrapper\FBXSDK.2019.2\lib"
The visual studio pre-compile macro automatically copy to output the correct "libfbxsdk.dll" versions. Remember that all your C# executable require the
presence of "libfbxsdk.dll" in the same folder (in FbxWrapperText I write the macro xcopy /d /f "$(SolutionDir)\FBXSDK.2019.2\lib\vs2017\$(PlatformName)\$(ConfigurationName)\libfbxsdk.dll" "" in the post-compiling)

- FbxWrapperTest.csproj is used to test the wrapper for managed code

- I will not convert all fbx sdk class, only those that serve to my purpose.

- I'm not a programmer but for some reason the code work, if you found compiling issue, ask me to johnwhilemail@gmail.com

