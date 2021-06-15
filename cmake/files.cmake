set(SIM_SOURCE_FILES

    "${PROJECT_SOURCE_DIR}/detector/detectorconstruction.cpp"

    "${PROJECT_SOURCE_DIR}/actions/actioninitialization.cpp"
    "${PROJECT_SOURCE_DIR}/actions/primarygeneratoraction.cpp"
    "${PROJECT_SOURCE_DIR}/actions/trackingaction.cpp"
    "${PROJECT_SOURCE_DIR}/actions/steppingaction.cpp"

    "${PROJECT_SOURCE_DIR}/analysis/recorder.cpp"

    "${PROJECT_SOURCE_DIR}/core.cpp"
    "${PROJECT_SOURCE_DIR}/main.cpp"
    )

set(SIM_HEADER_FILES
    "${PROJECT_INCLUDE_DIR}/detector/detectorconstruction.h"

    "${PROJECT_INCLUDE_DIR}/actions/actioninitialization.h"
    "${PROJECT_INCLUDE_DIR}/actions/primarygeneratoraction.h"
    "${PROJECT_INCLUDE_DIR}/actions/trackingaction.h"
    "${PROJECT_INCLUDE_DIR}/actions/steppingaction.h"

    "${PROJECT_INCLUDE_DIR}/analysis/recorder.h"
    "${PROJECT_INCLUDE_DIR}/analysis/histogram.h"

    "${PROJECT_INCLUDE_DIR}/core.h"
    )

set(ALL_SOURCES_AND_HEADERS
    "${SIM_SOURCE_FILES}"
    "${SIM_HEADER_FILES}"
    )
