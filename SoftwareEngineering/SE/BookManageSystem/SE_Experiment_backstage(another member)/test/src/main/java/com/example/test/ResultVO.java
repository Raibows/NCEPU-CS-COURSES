package com.example.test;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;

/**
 * @author 曾昭阳
 * @date 2020/6/1 13:22
 * <p>
 * 统一请求的返回格式
 */

@Data
@Setter
@Getter
public class ResultVO<T> {

    private int code;
    private String msg;
    private int type = 0;
    private T data;

    private ResultVO() {
    }

    public static ResultVO<Object> SUCCESS() {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(200);
        response.setMsg("操作成功");
        return response;
    }

    public static ResultVO<Object> SUCCESS(String msg) {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(200);
        response.setMsg(msg);
        return response;
    }

    public static ResultVO<Object> SUCCESS(String msg, int type) {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(200);
        response.setMsg(msg);
        response.setType(type);
        return response;
    }

    public static <T> ResultVO<T> SUCCESS(T data) {
        ResultVO<T> response = new ResultVO<>();
        response.setCode(200);
        response.setMsg("操作成功");
        response.setData(data);
        return response;
    }

    public static ResultVO<Object> FAIL() {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(300);
        response.setMsg("操作失败");
        return response;
    }

    public static ResultVO<Object> FAIL(String msg) {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(300);
        response.setMsg(msg);
        return response;
    }

    public static ResultVO<Object> FAIL(String msg, int type) {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(300);
        response.setMsg(msg);
        response.setType(type);
        return response;
    }

    public static ResultVO<Object> ERROR() {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(500);
        response.setMsg("操作失败");
        return response;
    }

    public static ResultVO<Object> ERROR(String msg) {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(500);
        response.setMsg(msg);
        return response;
    }

    public static ResultVO<Object> ERROR(String msg, int type) {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(500);
        response.setMsg(msg);
        response.setType(type);
        return response;
    }

    public static ResultVO<Object> UNAUTHORIZED() {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(401);
        response.setMsg("未授权");
        return response;
    }


    public static ResultVO<Object> UNAUTHORIZED(String msg) {
        ResultVO<Object> response = new ResultVO<>();
        response.setCode(401);
        response.setMsg(msg);
        return response;
    }

}
