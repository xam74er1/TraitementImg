##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TP8
ConfigurationName      :=Debug
WorkspacePath          :=/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8
ProjectPath            :=/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=BASSET Lucas
Date                   :=01/04/19
CodeLitePath           :=/users/info/etu-s4/bassetlu/.codelite
LinkerName             :=/usr/bin/x86_64-linux-gnu-g++
SharedObjectLinkerName :=/usr/bin/x86_64-linux-gnu-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
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
ObjectsFileList        :="TP8.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/x86_64-linux-gnu-ar rcu
CXX      := /usr/bin/x86_64-linux-gnu-g++
CC       := /usr/bin/x86_64-linux-gnu-gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/x86_64-linux-gnu-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyThresholdDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/opencv_bridge.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyHistogram.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyRotateDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/MyImage.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/MyThresholdDialog.cpp$(ObjectSuffix): MyThresholdDialog.cpp $(IntermediateDirectory)/MyThresholdDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/MyThresholdDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyThresholdDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyThresholdDialog.cpp$(DependSuffix): MyThresholdDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyThresholdDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyThresholdDialog.cpp$(DependSuffix) -MM MyThresholdDialog.cpp

$(IntermediateDirectory)/MyThresholdDialog.cpp$(PreprocessSuffix): MyThresholdDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyThresholdDialog.cpp$(PreprocessSuffix) MyThresholdDialog.cpp

$(IntermediateDirectory)/opencv_bridge.cpp$(ObjectSuffix): opencv_bridge.cpp $(IntermediateDirectory)/opencv_bridge.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/opencv_bridge.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opencv_bridge.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opencv_bridge.cpp$(DependSuffix): opencv_bridge.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opencv_bridge.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/opencv_bridge.cpp$(DependSuffix) -MM opencv_bridge.cpp

$(IntermediateDirectory)/opencv_bridge.cpp$(PreprocessSuffix): opencv_bridge.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opencv_bridge.cpp$(PreprocessSuffix) opencv_bridge.cpp

$(IntermediateDirectory)/MyHistogram.cpp$(ObjectSuffix): MyHistogram.cpp $(IntermediateDirectory)/MyHistogram.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/MyHistogram.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyHistogram.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyHistogram.cpp$(DependSuffix): MyHistogram.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyHistogram.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyHistogram.cpp$(DependSuffix) -MM MyHistogram.cpp

$(IntermediateDirectory)/MyHistogram.cpp$(PreprocessSuffix): MyHistogram.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyHistogram.cpp$(PreprocessSuffix) MyHistogram.cpp

$(IntermediateDirectory)/MyRotateDialog.cpp$(ObjectSuffix): MyRotateDialog.cpp $(IntermediateDirectory)/MyRotateDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/MyRotateDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyRotateDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyRotateDialog.cpp$(DependSuffix): MyRotateDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyRotateDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyRotateDialog.cpp$(DependSuffix) -MM MyRotateDialog.cpp

$(IntermediateDirectory)/MyRotateDialog.cpp$(PreprocessSuffix): MyRotateDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyRotateDialog.cpp$(PreprocessSuffix) MyRotateDialog.cpp

$(IntermediateDirectory)/MyImage.cpp$(ObjectSuffix): MyImage.cpp $(IntermediateDirectory)/MyImage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/MyImage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyImage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MyImage.cpp$(DependSuffix): MyImage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MyImage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MyImage.cpp$(DependSuffix) -MM MyImage.cpp

$(IntermediateDirectory)/MyImage.cpp$(PreprocessSuffix): MyImage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MyImage.cpp$(PreprocessSuffix) MyImage.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


