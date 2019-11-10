#include "CMakeLists.h"
#include <qtextstream.h>


CMakeLists::CMakeLists()
{
}


CMakeLists::~CMakeLists()
{
}

void CMakeLists::SetProjectName(const QString& name)
{
	projectName = name;
}

void CMakeLists::AddCMakeFlags(const QString& key, const QString& value)
{
	cmakeflags.insert(key, value);
}

void CMakeLists::AddDefine(const QString& value)
{
	defines.append(value);
}

void CMakeLists::AddIncludeDirectory(const QString& dir)
{
	includeDirectories.append(dir);
}

void CMakeLists::AddSource(const QString& key, const QString& value)
{
	sources.insert(key, value);
}

QString CMakeLists::GenerateCMakeLists()
{
	QString outputString;
	QTextStream ots(&outputString);

	ots << "cmake_minimum_required (VERSION 2.6)" << endl;
	ots << QString("project (%1)").arg(projectName) << endl;
	
	for (const auto& e : sources.keys()) {
		ots << QString("add_executable(%1 %2)").arg(e, sources.value(e)) << endl;
	}

	for (const auto& e : cmakeflags.keys()) {
		ots << QString("set (%1 %2)").arg(e, cmakeflags.value(e)) << endl;
	}

	if (defines.size() > 0) {
		QString def = "";
		for (const auto& e : defines) {
			def += "-D" + e + " ";
		}

		ots << QString("add_definitions(%1)").arg(def) << endl;
	}

	for (const auto& e : includeDirectories) {
		ots << QString("include_directories(%1)").arg(e) << endl;
	}
		
	return outputString;
}