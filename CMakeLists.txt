cmake_minimum_required(VERSION 3.5)

project(deezer-qt-client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools Network REQUIRED)

set(TS_FILES deezer-qt-client_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        api/deezer.cpp
        api/deezer.h

        api/util/json_serialization.h
        api/util/json_serialization.cpp

        api/object/compilation/chart.cpp
        api/object/compilation/chart.h
        api/object/compilation/editorial.cpp
        api/object/compilation/editorial.h

        api/object/playable/album.cpp
        api/object/playable/album.h
        api/object/playable/artist.cpp
        api/object/playable/artist.h
        api/object/playable/genre.cpp
        api/object/playable/genre.h
        api/object/playable/playlist.cpp
        api/object/playable/playlist.h
        api/object/playable/podcast.cpp
        api/object/playable/podcast.h
        api/object/playable/radio.cpp
        api/object/playable/radio.h
        api/object/playable/shared.h
        api/object/playable/track.cpp
        api/object/playable/track.h

        api/object/search/advanced_search_query.cpp
        api/object/search/advanced_search_query.h
        api/object/search/partial_search_response.h
        api/object/search/shared.h

        api/object/service/infos.cpp
        api/object/service/infos.h
        api/object/service/offer.cpp
        api/object/service/offer.h
        api/object/service/options.cpp
        api/object/service/options.h

        api/object/user/folder.cpp
        api/object/user/folder.h
        api/object/user/user.cpp
        api/object/user/user.h

        model/albumtracksmodel.h
        model/albumtracksmodel.cpp

        pages/albumpage.h
        pages/albumpage.cpp
        pages/albumpage.ui
        pages/artistpage.h
        pages/artistpage.cpp
        pages/artistpage.ui
        pages/mainpage.h
        pages/mainpage.cpp
        pages/mainpage.ui
        pages/pages.h
        pages/playlistpage.h
        pages/playlistpage.cpp
        pages/playlistpage.ui
        pages/radiopage.h
        pages/radiopage.cpp
        pages/radiopage.ui
        pages/searchpage.h
        pages/searchpage.cpp
        pages/searchpage.ui
        pages/userpage.h
        pages/userpage.cpp
        pages/userpage.ui

        resources.qrc

        widgets/albumcard.h
        widgets/albumcard.cpp
        widgets/albumcard.ui
        widgets/albumflow.h
        widgets/albumflow.cpp
        widgets/artistcard.h
        widgets/artistcard.cpp
        widgets/artistcard.ui
        widgets/artistflow.h
        widgets/artistflow.cpp
        widgets/flow.h
        widgets/playlistcard.h
        widgets/playlistcard.cpp
        widgets/playlistcard.ui
        widgets/playlistflow.h
        widgets/playlistflow.cpp
        widgets/radiocard.h
        widgets/radiocard.cpp
        widgets/radiocard.ui
        widgets/radioflow.h
        widgets/radioflow.cpp
        widgets/usercard.h
        widgets/usercard.cpp
        widgets/usercard.ui
        widgets/userflow.h
        widgets/userflow.cpp

        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(deezer-qt-client
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(deezer-qt-client SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(deezer-qt-client
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(deezer-qt-client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
