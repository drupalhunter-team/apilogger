--------------------------------
imex2spy v1.4 ReadMe
--------------------------------

Description
The program is micro helper tool for creating DB files for apilogger tool

Features:
-Dumps exported functions (by names, by ordinal) from EXE or DLL (also finds forwarded export functions)
-Dumps imported functions (by names, by ordinal) from EXE or DLL
-Optinally parses Delay Import and adds it into output DB
-was tested on > 100 input files (including famous yoda's 32bit PE file test corpus package)

----------------------
Format of DB
----------------------
[DLL_NAME.DLL]
FunctionName, ParamsCnt           - function defined by export name
!Ordinal, FunctionName, ParamsCnt - function defined by ordinal

You could edit DB file by hands after it was created.



----------------------
History
----------------------

     .2007 1.0 rustem           author of the tool
29.01.2011 1.1 sendersu took orig ver by (c)Rustem, 
                                fixed OriginalFirstThank(if 0), +D-n-D, topmost
                                +imp by ord, +exp by ord & fwd in comments
30.01.2011 1.2 sendersu imp/exp by ordinal - fixed output format (func names)
                                if pExport->Name not valid - take input dll name
01.02.2011 1.3 sendersu +cmdline support,
                                +delay import (with rvas flag analysis)
21.05.2011 1.4 sendersu   wow, bug fix in exporter (lots of missed func!)

Ideas and questions - http://cracklab.ru/f/

if you have some tricky exe/dll - send to rustem or sendersu
--------------------------------

icq: 404558476
email: black_ninja2000@mail.ru
www.blackninja2000.narod.ru
