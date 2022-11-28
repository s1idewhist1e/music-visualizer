//#include "gmock/gmock.h"
//#include "MusicVisualizer/Utils/Rendering/Renderer.h"
//#include "../../LoggerMock.h"
//#include "../Data/DatabaseMock.h"
//
//
//namespace mvlizer {
//	namespace tests {
//
//		using namespace mvlizer;
//		using ::testing::_;
//
//		class RendererTest : public ::testing::Test {
//		public:
//			
//			static Renderer* renderer;
//			static std::shared_ptr<MockLogger> logger;
//			static ::testing::NiceMock<MockDatabase> data;
//
//			static void SetUpTestSuite() {
//
//				logger = std::shared_ptr<MockLogger>(new MockLogger);
//				data = ::testing::NiceMock<MockDatabase>();
//
//				EXPECT_CALL(*logger, err)
//					.Times(0);
//				
//				renderer = new Renderer(logger, data);
//			}
//
//			static void TearDownTestSuite() {
//				delete renderer;
//			}
//		};
//
//		Renderer* RendererTest::renderer = nullptr;
//		std::shared_ptr<MockLogger> RendererTest::logger = nullptr;
//
//		TEST_F(RendererTest, glfwInitiaized) {
//			ASSERT_TRUE(glfwGetError(NULL) != GLFW_NOT_INITIALIZED);
//		}
//
//		//TEST_F(RenderTest, )
//
//
//		TEST_F(RendererTest, keycall) {
//			
//			//logger->error("sdfdf");
//
//			KeyInputInfo info{
//				0,
//				0
//			};
//			
//			auto first = Renderer::registerKeyCallback(info, [](KeyInputInfo info, GLFWwindow*) {});
//			bool eq = *first == NULL;
//			
//			ASSERT_TRUE(eq);
//			
//			auto second = Renderer::registerKeyCallback(info, NULL);
//
//			eq = *second == NULL;
//			//ASSERT_NE(prev, )
//			ASSERT_FALSE(eq);
//
//		}
//
//		class RendererTest_createWindow : RendererTest {
//		protected:
//			static void SetUpTestSuite() {
//				RendererTest::SetUpTestSuite();
//				renderer->createWindow();
//			}
//
//			static void TearDownTestSuite() {
//				renderer->destroyWindow();
//				RendererTest::TearDownTestSuite();
//			}
//		};
//
//		//TEST_F(RendererTest_createWindow, windowExists) {
//
//		//}
//
//	}
//}