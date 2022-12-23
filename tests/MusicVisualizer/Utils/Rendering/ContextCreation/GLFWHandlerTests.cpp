#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../LoggerMock.h"
#include "MusicVisualizer/Utils/Rendering/ContextCreation/GLFWHandler.h"

namespace mvlizer {
    namespace tests {
        using ::testing::Test;
        using ::testing::NiceMock;

        class GLFWHandlerTest : public ::testing::TestWithParam<contextCreationArgs> {
        protected:
            std::shared_ptr<NiceMock<MockLogger>> logger;
//
//            void SetUp() override {
//
//            };
//
//            void TearDown() override {
//
//            };

            void SetUp() override {
                logger = std::make_shared<NiceMock<MockLogger>>();
                std::shared_ptr<spikeylog::ILogger> logger_temp = logger;
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
                        contextCreationArgs{.width = 600, .height = 400, .title = "normal window"}
                        ),
                [](const ::testing::TestParamInfo<contextCreationArgs>& info) -> std::string {
                    auto str = info.param.title;
                    std::replace(str.begin(), str.end(), ' ', '_');
                    return str;
                }
        );

        TEST_F(GLFWHandlerTest, initializes) {
            EXPECT_CALL(*logger, err)
                    .Times(0);
            mvlizer::GLFWHandler::Init(logger);
            glfwGetKeyScancode(GLFW_KEY_0);
            EXPECT_NE(glfwGetError(nullptr), GLFW_NOT_INITIALIZED);
            mvlizer::GLFWHandler::Terminate();
        }

        TEST_F(GLFWHandlerTest, cannotInitializeTwice) {
            EXPECT_CALL(*logger, err)
                    .Times(testing::AtLeast(1));
            mvlizer::GLFWHandler::Init(logger);
            mvlizer::GLFWHandler::Init(logger);
            glfwGetKeyScancode(GLFW_KEY_0);
            EXPECT_NE(glfwGetError(nullptr), GLFW_NOT_INITIALIZED);
            GLFWHandler::Terminate();
        }

        TEST_F(GLFWHandlerTest, terminates) {

            EXPECT_CALL(*logger, err)
                .Times(0);
            GLFWHandler::Init(logger);
            GLFWHandler::Terminate();
            glfwGetKeyScancode(GLFW_KEY_0);
            ASSERT_EQ(glfwGetError(nullptr), GLFW_NOT_INITIALIZED);
            GLFWHandler::Init(logger);
            GLFWHandler::Terminate();
        }

        TEST_P(GLFWHandlerTest, createsWindow) {
            EXPECT_CALL(*logger, err)
                    .Times(0);
            GLFWHandler::Init(logger);
            auto args = GetParam();
            auto ctx = GLFWHandler::createContext(args);
            ASSERT_TRUE(ctx != nullptr);
            ASSERT_TRUE(ctx->window != nullptr);

            glfwMakeContextCurrent(ctx->window);
            GLFWwindow* window = glfwGetCurrentContext();
            EXPECT_EQ(window, ctx->window);

            int width, height;
            glfwGetWindowSize(ctx->window, &width, &height);

            EXPECT_EQ(width, args.width);
            EXPECT_EQ(height, args.height);
            GLFWHandler::Terminate();
        }

        TEST_P(GLFWHandlerTest, canDestroyContext) {
            EXPECT_CALL(*logger, err)
                .Times(0);
            GLFWHandler::Init(logger);
            auto ctx = GLFWHandler::createContext(GetParam());
            GLFWHandler::destroyContext(ctx);
            EXPECT_TRUE(ctx == nullptr);

            GLFWHandler::forEachContext([&ctx](Context*& context, const GLFWwindow* window) {
                EXPECT_TRUE(context != nullptr);
            });
            GLFWHandler::Terminate();
        }

        TEST_P(GLFWHandlerTest, canLoopThroughContexts) {
            EXPECT_CALL(*logger, err)
                .Times(0);
            GLFWHandler::Init(logger);
            std::vector<Context*> contexts;
            contexts.push_back(GLFWHandler::createContext(GetParam()));
            contexts.push_back(GLFWHandler::createContext(GetParam()));
            contexts.push_back(GLFWHandler::createContext(GetParam()));
            for (auto context : contexts) {
                bool glfw_has_context = false;
                GLFWHandler::forEachContext([&glfw_has_context, &context](Context* ctx, const GLFWwindow* win) {
                    if (ctx == context) {
                        glfw_has_context = true;
                    }
                });
                EXPECT_TRUE(glfw_has_context);
            }
            GLFWHandler::Terminate();
        }



    }
}
