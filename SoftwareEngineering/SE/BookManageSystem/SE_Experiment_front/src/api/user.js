import request from '@/utils/request'

export function login(data) {
  return request({
    url: '/maintain/login',
    method: 'post',
    data
  })
}

export function getUserByUserName(data) {
  return request({
    url: '/maintain/queryUserByName',
    method: 'post',
    data
  })
}

export function updateUser(data) {
  return request({
    url: '/maintain/updateUser',
    method: 'post',
    data
  })
}

export function addUser(data) {
  return request({
    url: '/maintain/addUser',
    method: 'post',
    data
  })
}

export function deleteUser(data) {
  return request({
    url: '/maintain/deleteUser',
    method: 'post',
    data
  })
}


