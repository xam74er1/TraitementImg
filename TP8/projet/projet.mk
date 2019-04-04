##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=projet
ConfigurationName      :=Debug
WorkspacePath          :=/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8
ProjectPath            :=/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/projet
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=BASSET Lucas
Date                   :=04/04/19
CodeLitePath           :=/users/info/etu-s4/bassetlu/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
ObjectsFileList        :="projet.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell wx-config --libs --unicode=yes) `pkg-config --libs opencv`
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes ) `pkg-config --cflags opencv` $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes ) `pkg-config --cflags opencv` $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/up_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_opencv_bridge.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_MyHistogram.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_MyRotateDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_MyImage.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_MyThresholdDialog.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/up_main.cpp$(ObjectSuffix): ../main.cpp $(IntermediateDirectory)/up_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_main.cpp$(DependSuffix): ../main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_main.cpp$(DependSuffix) -MM ../main.cpp

$(IntermediateDirectory)/up_main.cpp$(PreprocessSuffix): ../main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_main.cpp$(PreprocessSuffix) ../main.cpp

$(IntermediateDirectory)/up_opencv_bridge.cpp$(ObjectSuffix): ../opencv_bridge.cpp $(IntermediateDirectory)/up_opencv_bridge.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/opencv_bridge.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_opencv_bridge.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_opencv_bridge.cpp$(DependSuffix): ../opencv_bridge.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_opencv_bridge.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_opencv_bridge.cpp$(DependSuffix) -MM ../opencv_bridge.cpp

$(IntermediateDirectory)/up_opencv_bridge.cpp$(PreprocessSuffix): ../opencv_bridge.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_opencv_bridge.cpp$(PreprocessSuffix) ../opencv_bridge.cpp

$(IntermediateDirectory)/up_MyHistogram.cpp$(ObjectSuffix): ../MyHistogram.cpp $(IntermediateDirectory)/up_MyHistogram.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/MyHistogram.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_MyHistogram.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_MyHistogram.cpp$(DependSuffix): ../MyHistogram.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_MyHistogram.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_MyHistogram.cpp$(DependSuffix) -MM ../MyHistogram.cpp

$(IntermediateDirectory)/up_MyHistogram.cpp$(PreprocessSuffix): ../MyHistogram.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_MyHistogram.cpp$(PreprocessSuffix) ../MyHistogram.cpp

$(IntermediateDirectory)/up_MyRotateDialog.cpp$(ObjectSuffix): ../MyRotateDialog.cpp $(IntermediateDirectory)/up_MyRotateDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/MyRotateDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_MyRotateDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_MyRotateDialog.cpp$(DependSuffix): ../MyRotateDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_MyRotateDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_MyRotateDialog.cpp$(DependSuffix) -MM ../MyRotateDialog.cpp

$(IntermediateDirectory)/up_MyRotateDialog.cpp$(PreprocessSuffix): ../MyRotateDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_MyRotateDialog.cpp$(PreprocessSuffix) ../MyRotateDialog.cpp

$(IntermediateDirectory)/up_MyImage.cpp$(ObjectSuffix): ../MyImage.cpp $(IntermediateDirectory)/up_MyImage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/MyImage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_MyImage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_MyImage.cpp$(DependSuffix): ../MyImage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_MyImage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_MyImage.cpp$(DependSuffix) -MM ../MyImage.cpp

$(IntermediateDirectory)/up_MyImage.cpp$(PreprocessSuffix): ../MyImage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_MyImage.cpp$(PreprocessSuffix) ../MyImage.cpp

$(IntermediateDirectory)/up_MyThresholdDialog.cpp$(ObjectSuffix): ../MyThresholdDialog.cpp $(IntermediateDirectory)/up_MyThresholdDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/users/info/etu-s4/bassetlu/M4105C/TraitementImg/TP8/MyThresholdDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_MyThresholdDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_MyThresholdDialog.cpp$(DependSuffix): ../MyThresholdDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_MyThresholdDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_MyThresholdDialog.cpp$(DependSuffix) -MM ../MyThresholdDialog.cpp

$(IntermediateDirectory)/up_MyThresholdDialog.cpp$(PreprocessSuffix): ../MyThresholdDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_MyThresholdDialog.cpp$(PreprocessSuffix) ../MyThresholdDialog.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


