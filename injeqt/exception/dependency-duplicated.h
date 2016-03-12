/*
 * %injeqt copyright begin%
 * Copyright 2014 Rafał Malinowski (rafal.przemyslaw.malinowski@gmail.com)
 * %injeqt copyright end%
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include <injeqt/exception/invalid-dependency.h>

namespace injeqt { namespace v1 { namespace exception {

/**
 * @brief Exception is not thrown in Injeqt 1.1.
 * @todo Remove in Injeqt 2.0
 */
class INJEQT_API dependency_duplicated : public invalid_dependency
{

public:
	explicit dependency_duplicated(std::string what = std::string{});
	virtual ~dependency_duplicated();

};

}}}
