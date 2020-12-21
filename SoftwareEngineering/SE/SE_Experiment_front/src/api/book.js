import request from "@/utils/request";

export function queryBook(data) {
  return request({
    url: '/maintain/queryAllBook',
    method: 'post',
    data
  })
}

export function updateBook(data) {
  return request({
    url: '/maintain/updateBook',
    method: 'post',
    data
  })
}



