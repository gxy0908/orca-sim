/** 
 * This file is part of project URSA. More information on the project
 * can be found at 
 *
 * URSA's repository at GitHub: http://https://github.com/andersondomingues/ursa
 *
 * Copyright (C) 2018 Anderson Domingues, <ti.andersondomingues@gmail.com>
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
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. **/
//lib dependent includes
#include <iostream>
#include <queue>
#include <stdint.h>

//api includes
#include <UntimedModel.h>
#include <UComm.h>

/**
 * @brief Instiate a new bus with external storage (can be changed later via "MapTo(&)")
 * @param name A unique name to the bus (optional)
 * @param default_value A value to be read in case none has been set yet
 * @param addr A memory base to be used within memory mapping
 */
template <typename T>
UComm<T>::UComm(uint32_t addr, std::string name){
	_t_ptr  = &_t_storage;
	_t_addr = addr;
	_t_name = name;
};

/**
 * @brief Instiate a new bus with external storage (can be changed later via "MapTo()")
 * @param t_ptr
 * @param addr
 * @param name
 */
template <typename T>
UComm<T>::UComm(T* t_ptr, uint32_t addr, std::string name){
	_t_ptr  = t_ptr;
	_t_addr = addr;
	_t_name = name;
};

/**
* @brief Maps current comm to the internal storage
*/
template <typename T>
void UComm<T>::MapTo(){
	_t_ptr = &_t_storage;
}

/**
* @brief Maps current comm to an external storage and updates internal reference.
* @param addr
*/
template <typename T>
void UComm<T>::MapTo(T* addr){
	_t_ptr = addr;
}

/**
* @brief Maps current comm to an external storage and updates internal reference.
* @param addr
* @param m
*/
template <typename T>
void UComm<T>::MapTo(T* addr, uint32_t p){
	_t_ptr = addr;
	_t_addr = p;
}

/**
 * @brief Dtor.
 */
template <typename T>    
UComm<T>::~UComm(){
	//nothing to do
}

/**
 * @brief Read the value stored into the bus
 * @return the value
 */
template <typename T>
T UComm<T>::Read(){
	return *_t_ptr;
}
    
/**
 * @brief Set the value of the bus
 * @param val the value
 */
template <typename T>
void UComm<T>::Write(T val){
	*_t_ptr = val;
}

/**
 * @brief Set the value of the bus
 * @param val the value
 */
template <typename T>
void UComm<T>::Inc(T val){
	*_t_ptr = (*_t_ptr) + val;
}

/**
 * @brief Set the value of the bus
 * @param val the value
 */
template <typename T>
void UComm<T>::Dec(T val){
	*_t_ptr = (*_t_ptr) + val;
}

/**
 * @brief Get the memory mapping address
 * @return the address
 */
template <typename T>
uint32_t UComm<T>::GetAddress(){
	return _t_addr;
}

/**
 * @brief Get the name of the comm
 * @return the name (empty string if empty)
 */
template <typename T>
std::string UComm<T>::GetName(){
	return _t_name;
}