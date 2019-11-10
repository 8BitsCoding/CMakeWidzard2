#pragma once
#include <qstring.h>
#include <qmap.h>
#include <qlist.h>

class CMakeLists
{
public:
	CMakeLists();
	~CMakeLists();

	void SetProjectName(const QString&);
	void AddCMakeFlags(const QString&, const QString&);
	void AddDefine(const QString&);
	void AddIncludeDirectory(const QString&);
	void AddSource(const QString&, const QString&);

	QString GenerateCMakeLists();

private:
	QString projectName;
	QMap<QString, QString> cmakeflags;
	QList<QString> includeDirectories;
	QMap<QString, QString> sources;
	QList<QString> defines;
};

