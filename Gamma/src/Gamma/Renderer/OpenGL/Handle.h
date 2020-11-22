#ifndef GAMMA_OPENGL_HANDLE_H
#define GAMMA_OPENGL_HANDLE_H

#include "../../Gamma.h"
#include <stdint.h>

namespace Gamma {

	namespace OpenGL {

		class GAMMA_API Handle {
		public:
			Handle(void);
			virtual ~Handle(void) = default;
			uint32_t GetIdentifier(void);
			void SetIdentifier(uint32_t newID);
		protected:
			uint32_t Identifier;
		};

	}

}

#endif // !GAMMA_OPENGL_HANDLE_H

