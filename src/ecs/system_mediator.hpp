#pragma once

#include "system.hpp"

#include <vector>
#include <memory>

namespace engine {

	struct BaseMessage {};

	template<typename To, typename From, typename Data>
	struct Message: public BaseMessage {
		To recipiant;
		From sender;
		Data data;
	};


	class SystemMediator {
	public:

		void add(std::shared_ptr<System> sys) {
			systems.emplace_back(sys);
		}


		//------------------------------------------------------------------//
		// WARNING: Just pray to god no two systems ever have the same size //
		//------------------------------------------------------------------//
		template<typename T>
		std::shared_ptr<T> getSystem() {
			for (auto& sys : systems) {
				if (sizeof(T) == sys->size()) {
					return std::static_pointer_cast<T>(sys);
				}
			};
			throw std::runtime_error("EntityComponentSystemError: cannot get a system that does not exist");
		}


		template<typename To, typename From , typename Data>
		void* send(Data message) {
			messageBoard.emplace_back( Message{ To, From, message } );
		}

		void* receive() {

		}

	private:
		std::vector<std::shared_ptr<System>> systems{};
		std::vector<BaseMessage> messageBoard;
	};
}