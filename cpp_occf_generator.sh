#!/usr/bin/env bash

echo "info) recommend to set ClassNames as UpperCamelCase."
echo "info) Either awk or gsed(gnu sed) is required."

if [ "$1" = "-f" ]
then
  FILENAME=$2
  cat $FILENAME 2> /dev/null 1> /dev/null
  if [ $? != "0" ]
  then
    echo "file doesn't exist."
    exit 1
  fi
  CLASSES=$(cat $FILENAME)
else
  echo "usage) bash  $0  -f  filename"
  exit 1
fi
SRC_LIST=""

AWK=0
which awk > /dev/null
if [ $? == "0" ]
then
AWK=1
fi
which gsed > /dev/null
if [ $? != "0" ]
then
SED=sed
else
SED=gsed
fi

for CLASS_ENTRY in $CLASSES
do
  CLASS=$(basename $CLASS_ENTRY)
  CLASS_PATH=""
  if [ "$CLASS" != "$CLASS_ENTRY" ]; then
    CLASS_PATH="$(dirname $CLASS_ENTRY)"
  fi

  ls $CLASS_ENTRY.cpp 2> /dev/null && ls $CLASS_ENTRY.hpp 2> /dev/null
  SRC_LIST="\\
        $CLASS_ENTRY.cpp$SRC_LIST"
  if [ $? == "0" ]
  then
    echo "$CLASS_ENTRY: duplicated file name found."
    continue
  else
    echo "$CLASS_ENTRY: generated"
  fi
  if [ "$CLASS_PATH" != "" ]; then
    mkdir -p $CLASS_PATH
  fi
  touch $CLASS_ENTRY.hpp
  touch $CLASS_ENTRY.cpp
  if [ $AWK != "1" ]
  then
    HEADER_GUARD="$(echo $CLASS | $SED 's/[A-Z]/&/g' | $SED 's/[a-z]/\U&/g' | $SED 's/$/_HPP/')"
    LOWCAMELCASE_CLASS=$(echo $CLASS | $SED 's/[A-Z]/\L&/')
  else
    HEADER_GUARD="$(echo $CLASS | awk '{print toupper($0)}' | $SED 's/$/_HPP/')"
    LOWCAMELCASE_CLASS=$(echo $CLASS | awk '{print tolower($0)}')
  fi

##### file contents
HEADER_CONTENT="#ifndef $HEADER_GUARD
#define $HEADER_GUARD

class  $CLASS
{
public:
// constructors & destructor
  $CLASS();
  ~$CLASS();
  $CLASS(const $CLASS&);

// operators
  $CLASS\t&operator=(const $CLASS&);

// member functions
};

#endif // $HEADER_GUARD"
SOURCE_CONTENT="#include \"$CLASS.hpp\"

// constructors & destructor
$CLASS::$CLASS()
{
}

$CLASS::~$CLASS()
{
}

$CLASS::$CLASS(const $CLASS& arg)
{
  (void)$LOWCAMELCASE_CLASS;
}

// operators
$CLASS&
$CLASS::operator=(const $CLASS& arg)
{
  (void)$LOWCAMELCASE_CLASS;
  return *this;
}"
#####

  printf '%b\n' "$HEADER_CONTENT" > $CLASS_ENTRY.hpp
  printf '%b\n' "$SOURCE_CONTENT" > $CLASS_ENTRY.cpp

done

MAKEFILE_CONTENT="NAME    =  $FILENAME


CXX       :=  c++
CXXFLAGS  :=  -Wall -Wextra -Werror -std=c++98
LDFLAGS   :=
DEBUGFLAGS:=  -g -fsanitize=address
RM        :=  rm -f


SRC       :=  $SRC_LIST

TEMPLATE_SRC:=

OPEN_LIST :=  \$(SRC)\\
        \$(TEMPLATE_SRC)

OBJ       :=  \$(SRC:%.cpp=%.o)
DEP       :=  \$(OBJ:%.o=%.d)

STATE     :=  \$(shell ls DEBUG.mode 2> /dev/null)
ifeq (\$(STATE), DEBUG.mode)
CXXFLAGS  +=  \$(DEBUGFLAGS)
COMPILE_MODE:=  DEBUG.mode
else
COMPILE_MODE:=  RELEASE.mode
endif


.PHONY: all debug clean fclean re open

all: \$(COMPILE_MODE)
\t\$(MAKE) \$(NAME)

release: RELEASE.mode
\t\$(MAKE) all

debug: DEBUG.mode
\t\$(MAKE) all

RELEASE.mode:
\t\$(MAKE) fclean
\ttouch RELEASE.mode

DEBUG.mode:
\t\$(MAKE) fclean
\ttouch DEBUG.mode

clean:
\t\$(RM) \$(OBJ)
\t\$(RM) RELEASE.mode DEBUG.mode

fclean: clean
\t\$(RM) \$(NAME)

re: fclean
\t\$(MAKE) all

open:
\t@nvim -c ':tabdo let \$\$a=expand(\"%\") | let \$\$b=substitute(\$\$a, \"cpp\", \"hpp\", \"g\") | let \$\$c=trim(\$\$b) | vsplit \$\$c' -p \$(OPEN_LIST)

\$(NAME): \$(OBJ)
\t\$(CXX) \$^ \$(CXXFLAGS) -o \$@ \$(LDFLAGS)

\$(OBJ): %.o: %.cpp
\t\$(CXX) \$< \$(CXXFLAGS) -c -o \$@ \$(LDFLAGS)

-include \$(DEP)"

VIMSPECTOR="{
  \"configurations\": {
  \"C - Launch\": {
    \"adapter\": \"CodeLLDB\",
    \"configuration\": {
      \"name\": \"Cpp: Launch current file\",
      \"type\": \"lldb\",
      \"request\": \"launch\",
      \"externalConsole\": false,
      \"logging\": {
        \"engineLogging\": true
      },
      \"stopOnEntry\": true,
      \"stopAtEntry\": true,
      \"debugOptions\": [],
      \"MIMode\": \"lldb\",
      \"cwd\" : \"${cwd}\",
      \"args\" : [],
      \"program\": \"$FILENAME\"
    }
  }
  }
}"

read -p "Do you want to delete input file \"$FILENAME\"? (y/n)" RESPONSE
if [ $RESPONSE ]
then
  if [ $RESPONSE = "y" ]
  then
    rm $FILENAME
  fi
fi

read -p "Do you want to generate Makefile? (y/n)" RESPONSE
if [ "$RESPONSE" = "y" ]
then
  MAKEFILE_EXIST=$(ls Makefile 2> /dev/null 1> /dev/null; echo $?)
  if [ $MAKEFILE_EXIST = "0" ]
  then
    read -p "There exists Makefile already. Do you really want to generate Makefile? (y/n)" RESPONSE
  fi
  if [ "$RESPONSE" = "y" ] || [ $MAKEFILE_EXIST != "0" ]
  then

    printf '%b\n' "$MAKEFILE_CONTENT" > Makefile_temp
    cat Makefile_temp | sed 's/ $//' > Makefile
    rm Makefile_temp

  fi
fi

read -p "Do you want to generate .vimspector.json? (y/n)" RESPONSE
if [ "$RESPONSE" = "" ] || [ $RESPONSE != "y" ]
then
  exit 0
fi

touch .vimspector.json
printf '%b\n' "$VIMSPECTOR" > .vimspector.json
