#pragma once

#include <QtGui/QColor>

#include "../base/Export.hpp"
#include "Style.hpp"

namespace QtNodes
{
    class NODE_EDITOR_PUBLIC FlowViewStyle : public Style
    {
    public:
        FlowViewStyle();
        FlowViewStyle(QString jsonText);

        // modify style
        static void setStyle(QString jsonText);

    private:
        // load
        void loadJsonText(QString jsonText) override;
        void loadJsonFile(QString fileName) override;
        void loadJsonFromByteArray(QByteArray const &byteArray) override;

    public:
        QColor BackgroundColor;
        QColor FineGridColor;
        QColor CoarseGridColor;
    };
}
