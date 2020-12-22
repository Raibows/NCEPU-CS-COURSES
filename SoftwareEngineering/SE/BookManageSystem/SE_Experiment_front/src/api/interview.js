import request from "@/utils/request";

export function queryOrder(data) {
  return request({
    url: '/interview/queryOrder',
    method: 'post',
    data
  })
}

export function addOrder(data) {
  return request({
    url: '/interview/addOrder',
    method: 'post',
    data
  })
}

export function deleteOrder(data) {
  return request({
    url: '/interview/deleteOrder',
    method: 'post',
    data
  })
}

export function updateOrder(data) {
  return request({
    url: '/interview/updateOrder',
    method: 'post',
    data
  })
}
