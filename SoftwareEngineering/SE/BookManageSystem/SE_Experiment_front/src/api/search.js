import request from "@/utils/request";

export function queryAllBook(data) {
  return request({
    url: '/search/queryAllBook',
    method: 'post',
    data
  })
}
