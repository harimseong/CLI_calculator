NAME    =  computor


CXX       :=  c++
CXXFLAGS  :=  -Wall -Wextra -Werror -std=c++17
LDFLAGS   :=
DEBUGFLAGS:=  -g -fsanitize=address
RM        :=  rm -f


SRC       :=  \
        main.cpp\
        computing/data.cpp\
        computing/analyzer.cpp\
        computing/computer.cpp\
        parsing/ast.cpp\
        parsing/tokenizer.cpp\
        parsing/find_token.cpp\
        parsing/parser.cpp

TEMPLATE_SRC:=

OPEN_LIST :=  $(SRC)\
        $(TEMPLATE_SRC)

OBJ       :=  $(SRC:%.cpp=%.o)
DEP       :=  $(OBJ:%.o=%.d)

STATE     :=  $(shell ls .DEBUG 2> /dev/null)
ifeq ($(STATE), .DEBUG)
CXXFLAGS  +=  $(DEBUGFLAGS)
COMPILE_MODE:=  .DEBUG
else
COMPILE_MODE:=  .RELEASE
endif


.PHONY: all debug clean fclean re open

all: $(COMPILE_MODE)
	$(MAKE) $(NAME)

release: .RELEASE
	$(MAKE) all

debug: .DEBUG
	$(MAKE) all

.RELEASE:
	$(MAKE) fclean
	touch .RELEASE

.DEBUG:
	$(MAKE) fclean
	touch .DEBUG

clean:
	$(RM) $(OBJ)
	$(RM) .RELEASE .DEBUG

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

open:
	@nvim -c ':tabdo let $$a=expand("%") | let $$b=substitute($$a, "cpp", "hpp", "g") | let $$c=trim($$b) | vsplit $$c' -p $(OPEN_LIST)

jcd:
	bear -- make

$(NAME): $(OBJ)
	$(CXX) $^ $(CXXFLAGS) -o $@ $(LDFLAGS)

$(OBJ): %.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@ $(LDFLAGS)

-include $(DEP)
