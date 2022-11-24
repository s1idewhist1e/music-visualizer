#include "Database.h"

namespace mvlizer {
	Database::Database()
		: renderObjects(),
		should_close(false)
	{
	}

	void Database::setUpdateTime(double time) {
		update_mut.lock();
		updateTime = time;
		update_mut.unlock();
	}

	double Database::getUpdateTime() {
		update_mut.lock_shared();
		double val = updateTime;
		update_mut.unlock_shared();
		return val;
	}

	void Database::setRenderTime(double time) {
		render_mut.lock();
		renderTime = time;
		render_mut.unlock();
	}

	double Database::getRenderTime() {
		render_mut.lock_shared();
		double val = renderTime;
		render_mut.unlock_shared();
		return val;
	}

	Database::~Database() {
		for (auto ptr : renderObjects) {
			delete ptr;
		}
	}

}