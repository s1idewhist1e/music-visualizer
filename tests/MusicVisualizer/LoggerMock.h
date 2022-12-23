#pragma once
#ifndef LOGGER_MOCK_H
#define LOGGER_MOCK_H
#include <spikeylog.h>
#include <gtest/gtest.h>

namespace mvlizer {
	namespace tests {
		class MockLogger : public spikeylog::ILogger {
		public:
			//MOCK_METHOD(void, log, (std::string const& str_, spikeylog::LogLevel level), (override));
			//operator ILogger () { return this; }
			
			void log(std::string const& str, spikeylog::LogLevel level) {
				if (level > spikeylog::LogLevel::INFO) {
					err(str);
				}
			}

			MOCK_METHOD(void, err, (std::string str));

			MOCK_METHOD(void, enableLogLevel, (spikeylog::LogLevel level, int outId), (override));
			MOCK_METHOD(void, disableLogLevel, (spikeylog::LogLevel level, int outId), (override));
		};
	}
}
#endif