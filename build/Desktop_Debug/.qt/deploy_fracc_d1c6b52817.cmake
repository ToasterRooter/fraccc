include("/home/toster/fracc/build/Desktop_Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/fracc-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "/home/toster/fracc/build/Desktop_Debug/fracc"
    GENERATE_QT_CONF
)
