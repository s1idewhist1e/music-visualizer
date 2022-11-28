#pragma once
#ifndef LOGGER_MOCK_H
#define LOGGER_MOCK_H
#include <spikeylog.h>
#include <gtest/gtest.h>

namespace mvlizer {
	namespace tests {
		class MockLogger : public spikeylog::ILogger {
		public:
			//MOCK_METHOD(void, log, (std::string const& str, spikeylog::LogLevel level), (override));
			
			void log(std::string const& str, spikeylog::LogLevel level) {
				if (level > spikeylog::LogLevel::INFO) {
					err();
				}
			}

			MOCK_METHOD(void, err, ());

			MOCK_METHOD(void, enableLogLevel, (spikeylog::LogLevel level, int outId), (override));
			MOCK_METHOD(void, disableLogLevel, (spikeylog::LogLevel level, int outId), (override));
		};
	}
}
#endif