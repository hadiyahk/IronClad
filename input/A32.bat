:: -----------------------------------------------------------------------
:: COMPILERS COURSE - SCRIPT                                             -
:: SCRIPT A12 - CST8152 - Summer 2023                                    -
:: -----------------------------------------------------------------------

CLS
SET COMPILER=IronClad.exe

SET FILE0=INPUT0_Empty
SET FILE1 = INPUT1_STRING
SET FILE2 = INPUT2_DIGITS
SET FILES3 = INPUT3_IF_ELSE

SET ASSIGNMENT=A32
SET EXTENSION=ic
SET OUTPUT=out
SET ERROR=err

SET PARAM=P

:: -----------------------------------------------------------------------
:: Begin of Tests (A12 - S22)                                            -
:: -----------------------------------------------------------------------

@echo off

ECHO "###################################################"
ECHO "#                                                 #"
ECHO "#    ALGONQUIN         @@@@@@@         COLLEGE    #"
ECHO "#                  @@-----------@@                #"
ECHO "#               @@@@|  I R O N C L A D  |@@@@     #"
ECHO "#            @@@@@@@@-----------@@@@@@@@          #"
ECHO "#         @@@@@@@@@@@@@  @@@@@@@   @@@@@@@        #"
ECHO "#       @@@@@@@@@@@@@      @@@       @@@@@@       #"
ECHO "#     @@@@@@@    @@@@@    @@@@       @@@@@@@@     #"
ECHO "#    @@@@@@@       @@@@@ @@@@@@@    @@@@@@@@@@    #"
ECHO "#   @@@@@@@        @@@@@ @@@@@ @@@@@@    @@@@@@   #"
ECHO "#  @@@@@@@@@@    @@             @@@@      @@@@@@  #"
ECHO "#  @@@@@@@@@@@@@@@  @@@@@  @@@@  @@@@   @@    @@  #"
ECHO "# @@@@@@@@@@@@@@@   @@@@@ @@@@@   @@@@@@@@@    @@ #"
ECHO "# @@@@@      @@@@   @@@ @@@ @@@   @@@@    @@@@@@@ #"
ECHO "# @@@@        @@@@  @@@ @@@ @@@   @@@      @@@@@@ #"
ECHO "#  @@@@     @@@@@@@              @@@@@    @@@@@@  #"
ECHO "#  @@@@@@@@@@@     @@@  @@@   @@@    @@@@@@@@@@   #"
ECHO "#   @@@@@@@@@@@   @@@ @@@@@@ @@@@@    @@@@@@@@@   #"
ECHO "#    @@@@@@@@@@@@@@@ @@@@@@    @@@@@@@@@@@@@@@    #"
ECHO "#     @@@@@@@@@       @@@        @@@@@@@@@@@      #"
ECHO "#       @@@@@@         @@         @@@@@@@@@       #"
ECHO "#         @@@@@       @@@@@     @@@@@@@@@         #"
ECHO "#            @@@@@@@@@@@@@@@@@@@@@@@@@            #"
ECHO "#               @@@@@@@@@@@@@@@@@@@               #"
ECHO "#  COMPILERS        @@@@@@@@@@@        2023-S     #"
ECHO "#                                                 #"
ECHO "###################################################"
ECHO "                                                   "
ECHO "[READER SCRIPT ...................................]"
ECHO "                                                   "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A12 - S22) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE0%.%EXTENSION%	> %FILE0%-%ASSIGNMENT%.%OUTPUT%	2> %FILE0%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%

::
:: ADVANCED TESTS  -------------------------------------------------------
::
:: Advanced Tests (A12 - S22) - - - - - - - - -- - - - - - - - - - - -

%COMPILER% %PARAM% %FILE9%.%EXTENSION%	F 100 10	> %FILE9%-%ASSIGNMENT%-f-100-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-f-100-10.%ERROR%
%COMPILER% %PARAM% %FILE9%.%EXTENSION%	A 100 10	> %FILE9%-%ASSIGNMENT%-a-100-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-a-100-10.%ERROR%
%COMPILER% %PARAM% %FILE9%.%EXTENSION%	M 100 10	> %FILE9%-%ASSIGNMENT%-m-100-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-m-100-10.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: -----------------------------------------------------------------------
:: End of Tests (A12 - S22)                                              -
:: -----------------------------------------------------------------------
