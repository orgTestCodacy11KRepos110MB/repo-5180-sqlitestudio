#ifndef GENERICEXPORTPLUGIN_H
#define GENERICEXPORTPLUGIN_H

#include "exportplugin.h"
#include "genericplugin.h"

class GenericExportPlugin : public GenericPlugin, public ExportPlugin
{
    public:
        void initBeforeExport(Db* db, QIODevice* output, const ExportManager::StandardExportConfig& config);
        ExportManager::ExportModes getSupportedModes() const;
        CfgMain* getConfig() const;
        QString getConfigFormName(ExportManager::ExportMode mode) const;

    protected:
        Db* db = nullptr;
        QIODevice* output = nullptr;
        const ExportManager::StandardExportConfig* config = nullptr;
};

#endif // GENERICEXPORTPLUGIN_H
