cmake_minimum_required(VERSION 2.8.3)
project(ros_sensor_driver)



set(GPIO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../JetsonGPIO)
message(STATUS "path====: ${GPIO_PATH}")

include_directories(${GPIO_PATH}/include)
add_library(JetsonGPIO STATIC 
  ${GPIO_PATH}/src/JetsonGPIO.cpp
  ${GPIO_PATH}/src/PythonFunctions.cpp
  ${GPIO_PATH}/src/gpio_pin_data.cpp) #This finds this specific file

find_package(catkin REQUIRED 
  COMPONENTS 
  roscpp 
  rospy 
  std_msgs
  )

catkin_package()

include_directories(include
  ${catkin_INCLUDE_DIRS} 
)


add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})

add_executable(driver src/driver_node.cpp)
target_link_libraries(driver ${catkin_LIBRARIES} JetsonGPIO)
##include_directories(sensor-os/JetsonGPIO)
