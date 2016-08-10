##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Investing
ConfigurationName      :=Debug
WorkspacePath          := "/home/adrian/.codelite/Workspace_one"
ProjectPath            := "/home/adrian/.codelite/Workspace_one/Investing"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Adrian Michalek
Date                   :=10/08/16
CodeLitePath           :="/home/adrian/.codelite"
LinkerName             :=clang++
SharedObjectLinkerName :=clang++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Investing.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := clang++
CC       := clang
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/valuables.cpp$(ObjectSuffix) $(IntermediateDirectory)/title.cpp$(ObjectSuffix) $(IntermediateDirectory)/texture.cpp$(ObjectSuffix) $(IntermediateDirectory)/profit.cpp$(ObjectSuffix) $(IntermediateDirectory)/goal.cpp$(ObjectSuffix) $(IntermediateDirectory)/font.cpp$(ObjectSuffix) $(IntermediateDirectory)/engine.cpp$(ObjectSuffix) $(IntermediateDirectory)/currency.cpp$(ObjectSuffix) $(IntermediateDirectory)/chunk.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/attain.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/valuables.cpp$(ObjectSuffix): valuables.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/valuables.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/valuables.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/valuables.cpp$(PreprocessSuffix): valuables.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/valuables.cpp$(PreprocessSuffix) "valuables.cpp"

$(IntermediateDirectory)/title.cpp$(ObjectSuffix): title.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/title.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/title.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/title.cpp$(PreprocessSuffix): title.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/title.cpp$(PreprocessSuffix) "title.cpp"

$(IntermediateDirectory)/texture.cpp$(ObjectSuffix): texture.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/texture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/texture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/texture.cpp$(PreprocessSuffix): texture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/texture.cpp$(PreprocessSuffix) "texture.cpp"

$(IntermediateDirectory)/profit.cpp$(ObjectSuffix): profit.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/profit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/profit.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/profit.cpp$(PreprocessSuffix): profit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/profit.cpp$(PreprocessSuffix) "profit.cpp"

$(IntermediateDirectory)/goal.cpp$(ObjectSuffix): goal.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/goal.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/goal.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/goal.cpp$(PreprocessSuffix): goal.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/goal.cpp$(PreprocessSuffix) "goal.cpp"

$(IntermediateDirectory)/font.cpp$(ObjectSuffix): font.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/font.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/font.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/font.cpp$(PreprocessSuffix): font.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/font.cpp$(PreprocessSuffix) "font.cpp"

$(IntermediateDirectory)/engine.cpp$(ObjectSuffix): engine.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/engine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/engine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/engine.cpp$(PreprocessSuffix): engine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/engine.cpp$(PreprocessSuffix) "engine.cpp"

$(IntermediateDirectory)/currency.cpp$(ObjectSuffix): currency.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/currency.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/currency.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/currency.cpp$(PreprocessSuffix): currency.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/currency.cpp$(PreprocessSuffix) "currency.cpp"

$(IntermediateDirectory)/chunk.cpp$(ObjectSuffix): chunk.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/chunk.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/chunk.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/chunk.cpp$(PreprocessSuffix): chunk.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/chunk.cpp$(PreprocessSuffix) "chunk.cpp"

$(IntermediateDirectory)/attain.cpp$(ObjectSuffix): attain.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Investing/attain.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/attain.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/attain.cpp$(PreprocessSuffix): attain.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/attain.cpp$(PreprocessSuffix) "attain.cpp"

##
## Clean
##
clean:
	$(RM) -r ./Debug/


