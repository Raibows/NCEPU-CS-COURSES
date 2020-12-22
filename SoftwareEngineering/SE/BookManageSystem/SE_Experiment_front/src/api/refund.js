import request from "@/utils/request";

export function addRefund(data) {
  return request({
    url: '/maintain/addRefund',
    method: 'post',
    data
  })
}

export function findAllRefund(data) {
  return request({
    url: '/maintain/findAllRefund',
    method: 'post',
    data
  })
}
