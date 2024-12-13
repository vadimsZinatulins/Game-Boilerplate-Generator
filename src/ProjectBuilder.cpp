#include "ProjectBuilder.h"
#include "workspace.h"
#include "Logger.h"

// #include "math/MathExtensionBuilder.h"

#include "generators/WorkspaceGenerator.h"
#include "generators/CMakeListfilesGenerator.h"
#include "generators/ConfigFileGenerator.h"
#include "generators/KeyManagerGenerator.h"
#include "generators/MouseManagerGenerator.h"
#include "generators/TimeGenerator.h"
#include "generators/CronometerGenerator.h"
#include "generators/RandomGenerator.h"
#include "generators/ISceneGenerator.h"
#include "generators/MainSceneGenerator.h"
#include "generators/SceneManagerGenerator.h"
#include "generators/GameGenerator.h"
#include "generators/ProjectNameFileGenerator.h"
#include "generators/MainFileGenerator.h"

#include "generators/math/CoreGenerator.h"
#include "generators/math/Vec2Generator.h"
#include "generators/math/Vec3Generator.h"
#include "generators/math/Vec4Generator.h"
#include "generators/math/Mat2Generator.h"
#include "generators/math/Mat3Generator.h"


namespace gbg {

void ProjectBuilder::setProjectName(std::string projectName) {
	m_projectName = projectName;
}

void ProjectBuilder::setWithMathExtra(bool flag) {
	m_withMathExtra = flag;
}

void ProjectBuilder::setWithSdlImageExtra(bool flag) {
	m_withSdlImageExtra = flag;
}

void ProjectBuilder::build() {
	const auto projectName { m_projectName };
	const auto withMathExtra { m_withMathExtra };
	const auto withSdlImageExtra { m_withSdlImageExtra };

	auto workspaceGeneratorTask { WorkspaceGenerator(projectName, withMathExtra).generate() };
	auto cmakeListfilesGeneratorTask { CMakeListfilesGenerator(projectName, withSdlImageExtra, withMathExtra).generate(workspaceGeneratorTask) };
	auto configFileGeneratorTask { ConfigFileGenerator(projectName).generate(workspaceGeneratorTask) };
	auto keyManagerGeneratorTask { KeyManagerGenerator().generate(workspaceGeneratorTask) };
	auto mouseManagerGeneratorTask { MouseManagerGenerator().generate(workspaceGeneratorTask) };
	auto timeGeneratorTask { TimeGenerator().generate(workspaceGeneratorTask) };
	auto cronometerGeneratorTask { CronometerGenerator().generate(workspaceGeneratorTask) };
	auto randomGeneratorTask { RandomGenerator().generate(workspaceGeneratorTask) };
	auto isceneGeneratorTask { ISceneGenerator().generate(workspaceGeneratorTask) };
	auto mainSceneGeneratorTask { MainSceneGenerator().generate(workspaceGeneratorTask) };
	auto sceneManagerGeneratorTask { SceneManagerGenerator().generate(workspaceGeneratorTask) };
	auto gameGeneratorTask { GameGenerator().generate(workspaceGeneratorTask) };
	auto projectNameFileGeneratorTask { ProjectNameFileGenerator(projectName).generate(workspaceGeneratorTask) };
	auto mainFileGeneratorTask { MainFileGenerator(projectName).generate(workspaceGeneratorTask) };

	workspaceGeneratorTask->result();
	cmakeListfilesGeneratorTask->result();
	configFileGeneratorTask->result();
	keyManagerGeneratorTask->result();
	mouseManagerGeneratorTask->result();
	timeGeneratorTask->result();
	cronometerGeneratorTask->result();
	randomGeneratorTask->result();
	isceneGeneratorTask->result();
	mainSceneGeneratorTask->result();
	sceneManagerGeneratorTask->result();
	gameGeneratorTask->result();
	projectNameFileGeneratorTask->result();
	mainFileGeneratorTask->result();

	if(withMathExtra) {
		auto coreGeneratorTask { CoreGenerator().generate(workspaceGeneratorTask) };
		auto vec2GeneratorTask { Vec2Generator().generate(workspaceGeneratorTask) };
		auto vec3GeneratorTask { Vec3Generator().generate(workspaceGeneratorTask) };
		auto vec4GeneratorTask { Vec4Generator().generate(workspaceGeneratorTask) };
		auto mat2GeneratorTask { Mat2Generator().generate(workspaceGeneratorTask) };
		auto mat3GeneratorTask { Mat3Generator().generate(workspaceGeneratorTask) };

		coreGeneratorTask->result();
		vec2GeneratorTask->result();
		vec3GeneratorTask->result();
		vec4GeneratorTask->result();
		mat2GeneratorTask->result();
		mat3GeneratorTask->result();
	}

	Log().log("Project generated successfully");
	Log().log("Use the following command to build the project: cd " + projectName + " && cmake -B build/ && cmake --build build/");
}

}
