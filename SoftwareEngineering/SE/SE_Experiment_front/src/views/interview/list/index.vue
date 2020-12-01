<template>
  <div>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-input placeholder="请输入关键词（支持模糊搜索）" v-model="keyword" class="input-with-select"
                  @keydown.enter.native="search">
          <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
        </el-input>
      </el-col>
      <el-col :span="2" :offset="1" v-if="checkPermission(['user'])">
        <el-button type="primary" round @click="openForm()">添加采访清单</el-button>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="18" :offset="3" style="margin-top: 20px;">
        <el-table
          :data="tableData"
          border
          style="width: 100%"
          v-loading="loading">
          <el-table-column
            fixed
            prop="id"
            label="序号"
            width="150">
          </el-table-column>
          <el-table-column
            fixed
            prop="isbn"
            label="ISBN"
            width="150">
          </el-table-column>
          <el-table-column
            prop="bookName"
            label="书名">
          </el-table-column>
          <el-table-column
            prop="bookSeller"
            label="出版社">
          </el-table-column>
          <el-table-column
            prop="price"
            label="价格"
            width="80">
          </el-table-column>
          <el-table-column
            prop="name"
            label="填写人"
            width="100">
          </el-table-column>
          <el-table-column
            prop="orderDate"
            label="填写日期"
            width="100">
          </el-table-column>
          <el-table-column
            fixed="right"
            label="操作"
            width="180"
            v-if="checkPermission(['admin'])">
            <template slot-scope="scope">
              <el-button @click="addCheck(scope.row)" type="success" size="small">验收通过</el-button>
              <el-button @click="addRefund(scope.row)" type="danger" size="small">退货</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-pagination
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
          :current-page="currentPage"
          :page-sizes="[5, 10, 30, 50]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total">
        </el-pagination>
      </el-col>
    </el-row>
    <interview-interview ref="interview"/>
  </div>
</template>

<script>

import checkPermission from '@/utils/permission'
import {queryOrder} from "@/api/interview";
import InterviewInterview from "@/views/interview/list/components/interview";
import {addCheck} from "@/api/check";
import {addRefund} from "@/api/refund";

export default {
  name: 'Interview-List',
  components: {InterviewInterview},
  data() {
    return {
      loading: true,
      keyword: '',
      total: 0,
      currentPage: 1,
      pageSize: 10,
      tableData: []
    }
  },
  created() {
    this.search()
  },
  computed: {},
  methods: {
    checkPermission,
    search() {
      this.loading = true
      queryOrder({name: this.keyword, page: this.currentPage - 1, size: this.pageSize}).then(response => {
        this.loading = false
        this.tableData = response.data.content
        this.pageSize = response.data.pageable.pageSize
        this.currentPage = response.data.pageable.pageNumber + 1
        this.total = response.data.totalElements
      })
    },
    addCheck(row) {
      this.$confirm('此操作将标记该记录为验收通过, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        addCheck(row).then(response => {
          this.$message({
            type: 'success',
            message: response.msg
          });
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消'
        });
      });
    },
    addRefund(row) {
      this.$prompt('请输入退货原因', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
      }).then(({ value }) => {
        row.reason = value
        addRefund(row).then(response => {
          this.$message({
            type: 'success',
            message: response.msg
          });
          this.search()
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消'
        });
        this.search()
      });
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    },
    openForm() {
      this.$refs['interview'].visible = true;
    }
  }
}
</script>

<style lang="scss" scoped>

</style>
