TARGET = qtgeoservices_kokudo
QT += location-private positioning-private network

PLUGIN_TYPE = geoservices
PLUGIN_CLASS_NAME = QGeoServiceProviderFactoryKokudo
load(qt_plugin)

HEADERS += \
    qgeocodereplykokudo.h \
    qgeocodingmanagerenginekokudo.h \
    qgeomapreplykokudo.h \
    qgeoroutereplykokudo.h \
    qgeoroutingmanagerenginekokudo.h \
    qgeoserviceproviderpluginkokudo.h \
    qgeotiledmapkokudo.h \
    qgeotiledmappingmanagerenginekokudo.h \
    qgeotilefetcherkokudo.h \
    qplacecategoriesreplykokudo.h \
    qplacemanagerenginekokudo.h \
    qplacesearchreplykokudo.h

SOURCES += \
    qgeocodereplykokudo.cpp \
    qgeocodingmanagerenginekokudo.cpp \
    qgeomapreplykokudo.cpp \
    qgeoroutereplykokudo.cpp \
    qgeoroutingmanagerenginekokudo.cpp \
    qgeoserviceproviderpluginkokudo.cpp \
    qgeotiledmapkokudo.cpp \
    qgeotiledmappingmanagerenginekokudo.cpp \
    qgeotilefetcherkokudo.cpp \
    qplacecategoriesreplykokudo.cpp \
    qplacemanagerenginekokudo.cpp \
    qplacesearchreplykokudo.cpp


OTHER_FILES +=

DISTFILES += \
    kokudo_plugin.json

