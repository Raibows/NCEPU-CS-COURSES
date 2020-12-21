import request from "@/utils/request";

export function queryCheckList(data) {
  return request({
    url: '/check/queryOrder',
    method: 'post',
    data
  })
}

export function addCheck(data) {
  return request({
    url: '/check/addCheck',
    method: 'post',
    data
  })
}
