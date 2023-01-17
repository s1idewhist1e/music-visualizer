#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../LoggerMock.h"
#include "MusicVisualizer/Utils/Rendering/ContextCreation/GLFWHandler.h"

namespace mvlizer::rendering {
    namespace tests {
        using ::testing::Test;
        using ::testing::NiceMock;

        using mvlizer::rendering::GLFWHandler;

        class GLFWHandlerTest : public ::testing::TestWithParam<contextCreationArgs> {
        protected:
//            std::shared_ptr<NiceMock<mvlizer::tests::MockLogger>> logger;
//
//            void SetUp() override {
//
//            };
//
//            void TearDown() override {
//
//            };

            void SetUp() override {

//                std::shared_ptr<spikeylog::ILogger> logger_temp = logger;
            }

            void TearDown() override {
//                ::testing::Mock::VerifyAndClearExpectations(logger.get());
            }

        };

        INSTANTIATE_TEST_SUITE_P(
                ContextHints,
                GLFWHandlerTest,
                ::testing::Values(
                        contextCreationArgs{.width = 1, .height = 1, .title = "very small window"},
//                        contextCreationArgs{.width = 10000, .height = 10000, .title = "very large window"},
                        contextCreationArgs{.width = 600, .height = 400, .title = "normal window"},
                        contextCreationArgs{.fullscreen = true, .title = "fullscreen window"}
                        ),
                [](const ::testing::TestParamInfo<contextCreationArgs>& info) -> std::string {
                    auto str = info.param.title;
                    std::replace(str.begin(), str.end(), ' ', '_');
                    return str;
                }
        );

        TEST_F(GLFWHandlerTest, initializes) {
            auto logger = std::make_shared<NiceMock<mvlizer::tests::MockLogger>>();
            EXPECT_CALL(*logger, err)
                    .Times(0);
            GLFWHandler::GetInstance(logger);
            glfwGetKeyScancode(GLFW_KEY_0);
            EXPECT_NE(glfwGetError(nullptr), GLFW_NOT_INITIALIZED);
//            mvlizer::GLFWHandler::Terminate();
        }

        TEST_P(GLFWHandlerTest, createsWindow) {
            auto logger = std::make_shared<NiceMock<mvlizer::tests::MockLogger>>();

            EXPECT_CALL(*logger, err)
                    .Times(0);
            auto handler = GLFWHandler::GetInstance(logger);
            auto args = GetParam();
            auto ctx = handler->CreateWindow(args);
//            ASSERT_TRUE(ctx != nullptr);
            ASSERT_TRUE(ctx->window != nullptr);

            glfwMakeContextCurrent(ctx->window);
            GLFWwindow* window = glfwGetCurrentContext();
            EXPECT_EQ(window, ctx->window);

            int width, height;

            std::this_thread::sleep_for(std::chrono::seconds(1));

            glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &width, &height);

            int w, h;

            if(args.width > width || args.fullscreen) {
                w = width;
            } else {
                w = args.width;
            }

            if(args.height > height || args.fullscreen) {
                h = height;
            } else {
                h = args.height;
            }

            glfwGetWindowSize(ctx->window, &width, &height);


            EXPECT_EQ(width, w);
            EXPECT_EQ(height, h);

            handler->DestroyWindow();
        }

        TEST_P(GLFWHandlerTest, cannotCreateMultipleWindows) {
            auto logger = std::make_shared<NiceMock<mvlizer::tests::MockLogger>>();

            EXPECT_CALL(*logger, err)
                .Times(0);

            auto handler = GLFWHandler::GetInstance(logger);
            auto param = GetParam();
            handler->CreateWindow(param);
            EXPECT_THROW({
                handler->CreateWindow(param);
                }
                    , std::runtime_error);
            handler->DestroyWindow();
        }

        TEST_P(GLFWHandlerTest, cannotDestroyBeforeCreate) {
            auto logger = std::make_shared<NiceMock<mvlizer::tests::MockLogger>>();

            EXPECT_CALL(*logger, err)
                .Times(0);
            auto handler = GLFWHandler::GetInstance(logger);
            EXPECT_THROW({
                handler->DestroyWindow();
            }, std::runtime_error);
        }

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

        TEST_P(GLFWHandlerTest, cannotCallFromOtherThreads) {
            auto logger = std::make_shared<NiceMock<mvlizer::tests::MockLogger>>();
//            EXPECT_CALL(*logger, err)
//                .Times(testing::AtLeast(1));

            std::thread th([logger](){
                EXPECT_THROW({
                                 GLFWHandler::GetInstance(logger)->CreateWindow({});
                             }, std::runtime_error);
            });

//            std::this_thread::sleep_for(std::chrono::seconds(1));
            th.join();
        }

    }
}
