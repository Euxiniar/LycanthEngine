#pragma once
#include <vulkan/vulkan.h>
#include <Utils/Log.h>
#include <vector>

namespace Ly {
	class ValidationLayers {
	public: 
		ValidationLayers(const char* validationLayers);
		~ValidationLayers();
		
		std::vector<const char*>& get();

		static bool areEnabled();

	private:
		void areSupported();
		std::vector<const char*> m_validationLayers;
	};
}
