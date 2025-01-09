#!/usr/bin/env bash

echo "info) recommend to set ClassNames as UpperCamelCase."
echo "info) Either awk or gsed(gnu sed) is required."

CLASSES=
NAMESPACE=
TARGET=
while [ $# -gt 0 ]; do
  case "$1" in
  "-f")
    FILENAME=$2
    cat $FILENAME 2> /dev/null 1> /dev/null
    if [ $? != "0" ]
    then
      echo "file doesn't exist."
      exit 1
    fi
    if [ "${FILENAME:0:1}" == "_" ]; then
      TARGET=${FILENAME:1}
    else
      TARGET=$FILENAME
    fi

    CLASSES=$(cat $FILENAME)
    shift
    shift
  ;;
  "--ns")
    NAMESPACE="1"
    shift
  ;;
  *)
    echo "usage) bash  $0  -f  filename"
    exit 1
  ;;
  esac
done

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

  SRC_LIST="\\
        $CLASS_ENTRY.cpp$SRC_LIST"
  ls $CLASS_ENTRY.cpp >/dev/null 2>&1 && ls $CLASS_ENTRY.hpp >/dev/null 2>&1 
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
  if [ $AWK != "1" ]; then
    HEADER_GUARD="$(echo $CLASS | $SED 's/[A-Z]/&/g' | $SED 's/[a-z]/\U&/g' | $SED 's/$/_HPP/')"
    LOWCAMELCASE_CLASS=$(echo $CLASS | $SED 's/[A-Z]/\L&/')
  else
    HEADER_GUARD="$(echo $CLASS | awk '{print toupper($0)}' | $SED 's/$/_HPP/')"
    LOWCAMELCASE_CLASS=$(echo $CLASS | awk '{print tolower($0)}')
  fi
  NAMESPACE_BEGIN="\n"
  NAMESPACE_END="\n"
  if [ -n $NAMESPACE ]; then
    NAMESPACE_BEGIN="\nnamespace $(basename $CLASS_PATH)\n{\n"
    NAMESPACE_END="\n\n}"
  fi

##### file contents
HEADER_CONTENT="#ifndef $HEADER_GUARD
#define $HEADER_GUARD
$NAMESPACE_BEGIN
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
};$NAMESPACE_END

#endif // $HEADER_GUARD"
SOURCE_CONTENT="#include \"$CLASS.hpp\"
$NAMESPACE_BEGIN
// constructors & destructor
$CLASS::$CLASS()
{
}

$CLASS::~$CLASS()
{
}

$CLASS::$CLASS(const $CLASS& arg)
{
  (void)arg;
}

// operators
$CLASS&
$CLASS::operator=(const $CLASS& arg)
{
  (void)arg;
  return *this;
}$NAMESPACE_END"
#####

  printf '%b\n' "$HEADER_CONTENT" > $CLASS_ENTRY.hpp
  printf '%b\n' "$SOURCE_CONTENT" > $CLASS_ENTRY.cpp

done

SRC_LIST="\\
        main.cpp$SRC_LIST"
MAKEFILE_CONTENT="NAME    =  $TARGET


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

STATE     :=  \$(shell ls .DEBUG 2> /dev/null)
ifeq (\$(STATE), .DEBUG)
CXXFLAGS  +=  \$(DEBUGFLAGS)
COMPILE_MODE:=  .DEBUG
else
COMPILE_MODE:=  .RELEASE
endif


.PHONY: all debug clean fclean re open

all: \$(COMPILE_MODE)
\t\$(MAKE) \$(NAME)

release: .RELEASE
\t\$(MAKE) all

debug: DEBUG
\t\$(MAKE) all

.RELEASE:
\t\$(MAKE) fclean
\ttouch .RELEASE

.DEBUG:
\t\$(MAKE) fclean
\ttouch .DEBUG

clean:
\t\$(RM) \$(OBJ)
\t\$(RM) .RELEASE .DEBUG

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
  if [ "$RESPONSE" == "y" ]; then
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
