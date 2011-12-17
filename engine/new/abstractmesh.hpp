/****************************************************************************
 *            abstractmesh.hpp
 *
 * Author: 2011  Daniel Jungmann <el.3d.source@googlemail.com>
 * Copyright: See COPYING file that comes with this distribution
 ****************************************************************************/

#ifndef	UUID_e4486b52_0882_4250_9e47_1c776906bf13
#define	UUID_e4486b52_0882_4250_9e47_1c776906bf13

#ifndef	__cplusplus
#error	"Including C++ header in C translation unit!"
#endif	/* __cplusplus */

#include "prerequisites.hpp"

/**
 * @file
 * @brief The @c class AbstractMesh.
 * This file contains the @c class AbstractMesh.
 */
namespace eternal_lands
{

	/**
	 * @brief Abstract base @c class for meshs.
	 *
	 * Abstract base @c class for meshs.
	 */
	class AbstractMesh: public boost::noncopyable
	{
		private:

		protected:
			/**
			 * Default constructor.
			 */
			AbstractMesh();

		public:

			/**
			 * Default destructor.
			 */
			virtual ~AbstractMesh() throw();

			virtual void init() = 0;
			virtual void bind() = 0;
			virtual void draw() = 0;

	};

}

#endif	/* UUID_e4486b52_0882_4250_9e47_1c776906bf13 */

