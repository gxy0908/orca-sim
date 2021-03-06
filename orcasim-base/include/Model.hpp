/******************************************************************************
 * This file is part of project ORCA. More information on the project
 * can be found at the following repositories at GitHub's website.
 *
 * http://https://github.com/andersondomingues/orca-sim
 * http://https://github.com/andersondomingues/orca-software
 * http://https://github.com/andersondomingues/orca-mpsoc
 * http://https://github.com/andersondomingues/orca-tools
 *
 * Copyright (C) 2018-2020 Anderson Domingues, <ti.andersondomingues@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. 
******************************************************************************/
#ifndef ORCASIM_BASE_INCLUDE_MODEL_HPP_
#define ORCASIM_BASE_INCLUDE_MODEL_HPP_

#include <string>

namespace orcasim::base {

/**
 * Models a generic hardware model. Models usually correspond to modules, which
 * can be include any kind of hardware. Since not all the hardware behaviour is 
 * considered for simulation, we designed models to be either timed, when they 
 * obey to some clock domain, or untimed, when their clock is irrelevant for the
 * simulation. See <TimedModel> and <UntimedModel>.
 */
class Model {
 private:
    /**
     * A name for the model. Users may name models without any restriction, 
     * although we advise to give models meaningful names, as these names may
     * come in hand when debugging or reporting simulation.
     */
    std::string _name;

 public:
    /**
     * Default ctor. 
     * @name a name that identifies the model, advisably not empty.
     */
    explicit Model(std::string name);

    /**
     * Getter method for the <_name> field.
     */
    std::string GetName();

    /**
     * Setter method for the <_name> field.
     * @param s Value to be set
     */
    void SetName(std::string s);

    /**
     * Virtual destructor, must implement by subclass 
     */
    virtual ~Model() = 0;
};

}  // namespace orcasim::base
#endif  // ORCASIM_BASE_INCLUDE_MODEL_HPP_
