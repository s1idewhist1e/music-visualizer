//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#include "../../../LoggerMock.h"
//#include "MusicVisualizer/Utils/Rendering/ContextCreation/GLFWHandler.h"
//
//namespace mvlizer::rendering {
//    namespace tests {
//        using ::testing::Test;
//        using ::testing::NiceMock;
//
//    class GLFWHandlerTest : public ::testing::TestWithParam<mvlizer::rendering::contextCreationArgs> {
//        protected:
//            std::shared_ptr<NiceMock<mvlizer::tests::MockLogger>> logger;
////
////            void SetUp() override {
////
////            };
////
////            void TearDown() override {
////
////            };
//
//            void SetUp() override {
//                logger = std::make_shared<NiceMock<mvlizer::tests::MockLogger>>();
////                std::shared_ptr<spikeylog::ILogger> logger_temp = logger;
//            }
//
//            void TearDown() override {
////                ::testing::Mock::VerifyAndClearExpectations(logger.get());
//            }
//
//        };
//
//        INSTANTIATE_TEST_SUITE_P(
//                ContextHints,
//                GLFWHandlerTest,
//                ::testing::Values(
//                        contextCreationArgs{.width = 1, .height = 1, .title = "very small window"},
////                        contextCreationArgs{.width = 10000, .height = 10000, .title = "very large window"},
//                        contextCreationArgs{.width = 600, .height = 400, .title = "normal window"}
//                        ),
//                [](const ::testing::TestParamInfo<contextCreationArgs>& info) -> std::string {
//                    auto str = info.param.title;
//                    std::replace(str.begin(), str.end(), ' ', '_');
//                    return str;
//                }
//        );
//
//        TEST_F(GLFWHandlerTest, initializes) {
//            EXPECT_CALL(*logger, err)
//                    .Times(0);
//            mvlizer::GLFWHandler::GetInstance(logger);
//            glfwGetKeyScancode(GLFW_KEY_0);
//            EXPECT_NE(glfwGetError(nullptr), GLFW_NOT_INITIALIZED);
////            mvlizer::GLFWHandler::Terminate();
//        }
//
//        TEST_P(GLFWHandlerTest, createsWindow) {
//            EXPECT_CALL(*logger, err)
//                    .Times(0);
//            auto handler = mvlizer::GLFWHandler::GetInstance(logger);
//            auto args = GetParam();
//            auto ctx = handler->CreateWindow(args);
////            ASSERT_TRUE(ctx != nullptr);
//            ASSERT_TRUE(ctx.load()->window != nullptr);
//
//            glfwMakeContextCurrent(ctx.load()->window);
//            GLFWwindow* window = glfwGetCurrentContext();
//            EXPECT_EQ(window, ctx.load()->window);
//
//            int width, height;
//
//            glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &width, &height);
//
//            int w, h;
//
//            if(args.width > width) {
//                w = width;
//            } else {
//                w = args.width;
//            }
//
//            if(args.height > height) {
//                h = height;
//            } else {
//                h = args.height;
//            }
//
//            glfwGetWindowSize(ctx.load()->window, &width, &height);
//
//
//            EXPECT_EQ(width, w);
//            EXPECT_EQ(height, h);
//        }
//
//        TEST_P(GLFWHandlerTest, canDestroyContext) {
//            EXPECT_CALL(*logger, err)
//                .Times(0);
//            auto handler = GLFWHandler::GetInstance(logger);
//            auto ctx = handler->CreateWindow(GetParam());
//
//            auto callback = glfwSetErrorCallback(nullptr);
//
//            glfwGetKeyScancode(GLFW_KEY_0);
//            EXPECT_EQ(glfwGetError(nullptr), GLFW_NOT_INITIALIZED);
//
//            glfwSetErrorCallback(callback);
//
//        }
//
//    }
//}
